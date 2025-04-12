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
|         0 | *    | *      |  100 |                                 |                               |
|           |      | 0      |      | *(unused)*                      |                               |
|           |      | 1      |      | Name                            |                               |
|           |      | 2      |      | Active                          |                               |
|           |      | 3..9   |      | *(unused)*                      |                               |
| **1..64** | *    | *      | 6400 | **Channel-specific parameters** | N[0]*10+N[1] = Channel Number |
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
|    70..99 | *    | *      | 3000 |                                 |                               |




## ComObjects