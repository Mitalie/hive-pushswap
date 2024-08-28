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

### Extra passes

* 2nd extra pass first useful at size 250
* 3rd extra pass first useful at size 2698
* 4th extra pass first useful at size 21332

### Polyphase merge passes

|   A1 |   A2 |   B1 |   B2 | total runs | pass size |
|-----:|-----:|-----:|-----:|-----------:|----------:|
|    1 |    0 |    0 |    0 |          1 |         1 |
|    0 |    1 |    1 |    1 |          3 |         1 |
|    1 |    0 |    2 |    2 |          5 |         2 |
|    3 |    2 |    0 |    4 |          9 |         4 |
|    7 |    6 |    4 |    0 |         17 |         7 |
|    0 |   13 |   11 |    7 |         31 |        13 |
|   13 |    0 |   24 |   20 |         57 |        24 |
|   37 |   24 |    0 |   44 |        105 |        44 |
|   81 |   68 |   44 |    0 |        193 |        81 |
|    0 |  149 |  125 |   81 |        355 |       149 |
|  149 |    0 |  274 |  230 |        653 |       274 |
|  423 |  274 |    0 |  504 |       1201 |       504 |
|  927 |  778 |  504 |    0 |       2209 |       927 |
|    0 | 1705 | 1431 |  927 |       4063 |      1705 |
| 1705 |    0 | 3136 | 2632 |       7473 |      3136 |

### Presort triplet to B

123  pb pb pb           +0/3
132  sa pb pb pb        +1/3
213  pb sa pb pb        +1/3
231  sa pb sa pb pb     +2/3
312  pb sa pb sb pb     +2/3
321  sa pb sa pb sb pb  +3/3
