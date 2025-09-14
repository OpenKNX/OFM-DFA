# Numbering

## Parameters

* Special: Use numbering TCCNNNN (99 channels / 10000 parameters)
  * instaed of TCCCNNN (999 channels / 1000 parameters).

With:
* T = Module Number
* CC = Channel Number
* NNNN = Parameter Number

### Overall

### by Channel

|   N[0..1] | N[2] | N[3]   |    # | Area/Name                       | Description                   |
|----------:|------|--------|-----:|---------------------------------|-------------------------------|
|         0 | 0    | *      |  100 | **Start and control settings**  |                               |
|           | 1..8 | *      |      | *(unused)*                      |                               |
|           | 9    | 0      |      | Comment                         |                               |
|           | 9    | 1..9   |      | *(unused)*                      |                               |
| **1..64** | *    | *      | 6400 | **State-specific parameters**   | N[0]*10+N[1] = State Number   |
|           | 0    | 0      |      | State Name                      |                               |
|           | 0    | 1..8   |      | Following State by Input        |                               |
|           | 0    | 9      |      | *(unused)*                      | reserved for input 9          |
|           | 1    | 0..6   |      | *(unused)*                      | reserved for input 10..16     |
|           | 1    | 7      |      | Following State by Timeout      |                               |
|           | 1    | 8      |      | Timeout Time                    |                               |
|           | 1    | 9      |      | Timeout Unit                    |                               |
|           | 2..3 | *      |      | **output1**                     |                               |
|           | 4..5 | *      |      | **output2**                     |                               |
|           | 6..7 | *      |      | **output3**                     |                               |
|           | 8..9 | *      |      | **output4**                     |                               |
|    65..69 | *    | *      |  600 | *(unused)*                      |                               |
|        70 | *    | *      |  100 |                                 |                               |
|           | 0    | *      |      | **Symbol pair configurations**  |                               |
|           | 1..9 | *      |      | *(unused)*                      |                               |
|    71..79 | 0    | *      |  900 | **Input symbol definitions**    | 'A'=71 .. 'H'=78 + 'T'=79     |
|           | 1..9 | *      |      | *(unused)*                      |                               |
|        80 | *    | *      |  100 | *(unused)*                      |                               |
|    81..84 | 0    | *      |  400 | **Output definitions**          |                               |
|           | 1..9 | *      |      | *(unused)*                      |                               |
|    85..99 | *    | *      | 1500 | *(unused)*                      |                               |




## ComObjects