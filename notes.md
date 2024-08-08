# push_swap

## Flow

entry
    validate and count args
    calculate run buffer sizes
        minimum: runs > items (assuming no presort)
        make space for a few extra iterations to allow selecting cheaper options
        * may be obsolete with presort
        * presort may allow finishing with *fewer* iterations too
    allocate run buffers
    split runs, track costs
    * current bottom +1, other top +1, other bottom +2
    * items on B cost extra +1 for balancing
    select N cheapest runs and calculate total cost
        sort by cost, select first N
        * O(n^2) is borderline, implement O(n log n)
        presort into cheap runs to avoid most expensive runs?
        * pair to B? (cost +1 worst, +0.5 avg for the second item)
        * triplet to B? (cost +2 worst, +1 avg for the third item)
        * pair to A?
            cost +1 worst, +0.5 avg for the second item
            everything below the first pair (except top) needs +1 per item to rotate
            can be worth moving a few entries from most expensive runs to cheap runs on bottom
            cost changes during selection, requires adjusting order (bubblesort?)
            how to express cost? too frontloaded prevents selection
        * bigger groups? 4 to B, 8 moves total = +1 worst for 4th item
    test a few additional split iterations for lowest sum
    * or fewer iterations? possible with presorts
    replace costs with run lengths
    allocate and fill data buffers
    balance stacks according to run distribution (and presort according to lengths+directions)
    merge runs based on data, output operations

### Presort triplet to B

123  pb pb pb           +0/3
132  sa pb pb pb        +1/3
213  pb sa pb pb        +1/3
231  sa pb sa pb pb     +2/3
312  pb sa pb sb pb     +2/3
321  sa pb sa pb sb pb  +3/3
