#!/bin/bash

n=256

declare -i output=0
declare -i pb=0
declare -i rra=0
declare -i rrb=0
declare -i rrr=0

trial(){
    #d=$(seq 0 $((n-1))) # sorted
    #d=$(seq $((n-1)) -1 0) # reverse sorted
    d=$(shuf -i 0-$((n-1))) # random
    exec 3< <(head -n $((n/2)) <<<$d | sort -n)
    exec 4< <(tail -n +$((n/2+1)) <<<$d | sort -n)

    declare -i na=n/2
    declare -i nb=n-n/2
    read a <&3
    read b <&4
    declare -i did_rrr=0
    while ((na || nb)); do
        if (( na && (!nb || a < b) )); then
            if ((!did_rrr && nb)); then
                ((rrr++))
                did_rrr=1
            else
                ((rra++))
            fi
            ((output)) && echo a $a
            read a <&3
            ((na--))
        else
            if ((!did_rrr)); then
                ((rrb++))
            fi
            ((pb++))
            did_rrr=0
            ((output)) && echo b $b
            read b <&4
            ((nb--))
        fi
    done
}

if (($#)); then
    for ((i=0;i<$1;i++)); do trial; done
    declare -i totops=pb+rra+rrb+rrr
    declare -i totmerged=$1*n
    declare -i whole=totops/totmerged
    declare -i frac=totops*1000/totmerged%1000
    echo $whole.$frac
else
    output=1
    trial
    echo $pb pb
    echo $rra rra
    echo $rrb rrb
    echo $rrr rrr
    echo total $((pb+rra+rrb+rrr))
    echo naive $((pb+rra+rrb+rrr+rrr))
fi

