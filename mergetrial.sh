#!/bin/bash

declare -i n=300

declare -i output=0
declare -i pb=0
declare -i rra=0
declare -i rrb=0
declare -i rrr=0
declare -i pa=0
declare -i ra=0
declare -i rb=0
declare -i rr=0

merge_trial(){
    # a = same stack bottom
    # b = other stack top
    # c = other stack bottom
    declare -i na=n/3
    declare -i nb=n/3
    declare -i nc=n-na-nb

    #d=$(seq 0 $((n-1))) # sorted
    d=$(seq $((n-1)) -1 0) # reverse sorted
    #d=$(shuf -i 0-$((n-1))) # random
    exec 3< <(head -n $na <<<$d | sort -n)
    exec 4< <(tail -n +$((na+1)) <<<$d | head -n $nb | sort -n)
    exec 5< <(tail -n +$((na+nb+1)) <<<$d | sort -n)

    read a <&3
    read b <&4
    read c <&5
    declare -i did_rrr=0
    while ((na || nb || nc)); do
        if ((na && (!nb || a < b) && (!nc || a < c))); then
            if ((!did_rrr && nc && (!nb || c < b))); then
                ((rrr++))
                did_rrr=1
            else
                ((rra++))
            fi
            ((output)) && echo a $a
            read a <&3
            ((na--))
        elif ((nb && (!nc || b < c))); then
            ((pb++))
            ((output)) && echo b $b
            read b <&4
            ((nb--))
        else
            if ((!did_rrr)); then
                ((rrb++))
            fi
            ((pb++))
            did_rrr=0
            ((output)) && echo c $c
            read c <&5
            ((nc--))
        fi
    done
}

radix_trial(){
    #d=$(seq 0 $((n-1))) # sorted
    #d=$(seq $((n-1)) -1 0) # reverse sorted
    d=$(shuf -i 0-$((n-1))) # random
    exec 3<<<$d
    declare -i la=n/3
    declare -i lb=la+n/3

    declare -i rb_deficit=0
    while read it <&3; do
        if ((it<la)); then
            ((output)) && echo a $it
            if ((rb_deficit)); then
                ((rb_deficit--))
                ((rr++))
            else
                ((ra++))
            fi
        elif ((it<lb)); then
            ((output)) && echo b $it
            while ((rb_deficit)); do
                ((rb_deficit--))
                ((rb++))
            done
            ((pa++))
        else
            ((output)) && echo c $it
            ((pa++))
            ((rb_deficit++))
        fi
    done
    while ((rb_deficit)); do
        ((rb_deficit--))
        ((rb++))
    done
}

if (($#)); then
    for ((i=0;i<$1;i++)); do
        #merge_trial
        radix_trial
    done
    #declare -i totops=pb+rra+rrb+rrr
    declare -i totops=pa+ra+rb+rr
    declare -i totmerged=$1*n
    declare -i whole=totops/totmerged
    declare -i frac=totops*100000/totmerged%100000
    echo $whole.$frac
else
    output=1
    #merge_trial
    #echo $pb pb
    #echo $rra rra
    #echo $rrb rrb
    #echo $rrr rrr
    #echo total $((pb+rra+rrb+rrr))
    #echo naive $((pb+rra+rrb+rrr+rrr))
    radix_trial
    echo $pa pa
    echo $ra ra
    echo $rb rb
    echo $rr rr
    echo total $((pa+ra+rb+rr))
    echo naive $((pa+ra+rb+rr+rr))
fi

