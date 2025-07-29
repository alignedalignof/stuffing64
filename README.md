# 8 vs 64 bit stuffing
Motivation
----------
8-bit processing on a 64-bit puter is sevenbitsignedascii

WSL
---
```
./stuff64
dry run
[  OK]memcpy      1024 MiB, enc    657.883, dec    588.106, total   1245.989 [ms] 0.862 GiB/s
[  OK]COBS        1024 MiB, enc    474.506, dec    528.210, total   1002.716 [ms] 1.071 GiB/s
[  OK]COBS64      1024 MiB, enc    113.483, dec    127.175, total    240.658 [ms] 4.462 GiB/s
[  OK]z2          1024 MiB, enc    102.205, dec    135.145, total    237.350 [ms] 4.524 GiB/s
[  OK]evenify     1024 MiB, enc     99.345, dec    135.867, total    235.212 [ms] 4.565 GiB/s
[  OK]oddify      1024 MiB, enc    104.635, dec    124.416, total    229.051 [ms] 4.688 GiB/s
zero data
[  OK]memcpy      1024 MiB, enc     55.293, dec     54.860, total    110.153 [ms] 9.748 GiB/s
[  OK]COBS        1024 MiB, enc    424.995, dec    474.140, total    899.135 [ms] 1.194 GiB/s
[  OK]COBS64      1024 MiB, enc    134.374, dec    128.356, total    262.730 [ms] 4.087 GiB/s
[  OK]z2          1024 MiB, enc    147.428, dec    117.429, total    264.857 [ms] 4.054 GiB/s
[  OK]evenify     1024 MiB, enc    145.997, dec    130.709, total    276.706 [ms] 3.880 GiB/s
[  OK]oddify      1024 MiB, enc    147.075, dec    119.336, total    266.411 [ms] 4.030 GiB/s
0xff data
[  OK]memcpy      1024 MiB, enc     56.908, dec     52.738, total    109.646 [ms] 9.793 GiB/s
[  OK]COBS        1024 MiB, enc    526.901, dec    353.944, total    880.845 [ms] 1.219 GiB/s
[  OK]COBS64      1024 MiB, enc    118.402, dec    119.357, total    237.759 [ms] 4.516 GiB/s
[  OK]z2          1024 MiB, enc    115.779, dec    104.931, total    220.710 [ms] 4.865 GiB/s
[  OK]evenify     1024 MiB, enc    136.985, dec    137.812, total    274.797 [ms] 3.907 GiB/s
[  OK]oddify      1024 MiB, enc    150.226, dec    132.273, total    282.499 [ms] 3.801 GiB/s
pseudo data
[  OK]memcpy      1024 MiB, enc     59.803, dec     58.909, total    118.712 [ms] 9.045 GiB/s
[  OK]COBS        1024 MiB, enc    557.611, dec    370.285, total    927.896 [ms] 1.157 GiB/s
[  OK]COBS64      1024 MiB, enc    126.957, dec    115.896, total    242.853 [ms] 4.421 GiB/s
[  OK]z2          1024 MiB, enc    128.541, dec    122.300, total    250.841 [ms] 4.281 GiB/s
[  OK]evenify     1024 MiB, enc    143.681, dec    133.781, total    277.462 [ms] 3.870 GiB/s
[  OK]oddify      1024 MiB, enc    135.090, dec    124.863, total    259.953 [ms] 4.131 GiB/s
```
wonkydose
```
stuff64.exe
dry run
[  OK]memcpy      1024 MiB, enc    322.463, dec    238.443, total    560.906 [ms] 1.914 GiB/s
[  OK]COBS        1024 MiB, enc    402.684, dec    364.782, total    767.466 [ms] 1.399 GiB/s
[  OK]COBS64      1024 MiB, enc    138.478, dec    117.247, total    255.725 [ms] 4.199 GiB/s
[  OK]z2          1024 MiB, enc    186.822, dec    149.480, total    336.302 [ms] 3.193 GiB/s
[  OK]evenify     1024 MiB, enc    137.516, dec    126.960, total    264.476 [ms] 4.060 GiB/s
[  OK]oddify      1024 MiB, enc    138.696, dec    158.846, total    297.542 [ms] 3.609 GiB/s
zero data
[  OK]memcpy      1024 MiB, enc     79.771, dec     78.486, total    158.257 [ms] 6.785 GiB/s
[  OK]COBS        1024 MiB, enc    404.133, dec    407.242, total    811.375 [ms] 1.323 GiB/s
[  OK]COBS64      1024 MiB, enc    121.558, dec    117.255, total    238.813 [ms] 4.496 GiB/s
[  OK]z2          1024 MiB, enc    156.117, dec    136.172, total    292.289 [ms] 3.674 GiB/s
[  OK]evenify     1024 MiB, enc    145.194, dec    115.134, total    260.328 [ms] 4.125 GiB/s
[  OK]oddify      1024 MiB, enc    142.825, dec    128.361, total    271.186 [ms] 3.959 GiB/s
0xff data
[  OK]memcpy      1024 MiB, enc     79.713, dec     78.479, total    158.192 [ms] 6.788 GiB/s
[  OK]COBS        1024 MiB, enc    497.604, dec    415.493, total    913.097 [ms] 1.176 GiB/s
[  OK]COBS64      1024 MiB, enc    117.115, dec    112.033, total    229.148 [ms] 4.686 GiB/s
[  OK]z2          1024 MiB, enc    117.486, dec    114.295, total    231.781 [ms] 4.633 GiB/s
[  OK]evenify     1024 MiB, enc    150.511, dec    145.295, total    295.806 [ms] 3.630 GiB/s
[  OK]oddify      1024 MiB, enc    144.519, dec    136.374, total    280.893 [ms] 3.823 GiB/s
pseudo data
[  OK]memcpy      1024 MiB, enc     80.304, dec     81.869, total    162.173 [ms] 6.621 GiB/s
[  OK]COBS        1024 MiB, enc    544.473, dec    455.000, total    999.473 [ms] 1.074 GiB/s
[  OK]COBS64      1024 MiB, enc    131.129, dec    127.770, total    258.899 [ms] 4.147 GiB/s
[  OK]z2          1024 MiB, enc    132.176, dec    124.520, total    256.696 [ms] 4.183 GiB/s
[  OK]evenify     1024 MiB, enc    145.101, dec    131.099, total    276.200 [ms] 3.888 GiB/s
[  OK]oddify      1024 MiB, enc    148.623, dec    127.279, total    275.902 [ms] 3.892 GiB/s
```
