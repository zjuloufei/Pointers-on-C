"""反向间隙补偿，看看效果"""
# 有几个轴效果好，有几个轴效果不好

import matplotlib.pyplot as plt
import copy

# 存放各轴位置的两个二位数组
data_before = []
data_after =  []

# 将数据存入到数组中
with open('before_backlash_nm_or_udeg.txt') as f:
    for line in f.readlines():
        temp  = line.split()
        data_before.append(list(map(int, temp)))

with open('after_backlash_nm_or_udeg.txt') as f:
    for line in f.readlines():
        temp  = line.split()
        data_after.append(list(map(int, temp)))

# 把数据转置一下
data_before_T = list(map(list, zip(*data_before)))
data_after_T  = list(map(list, zip(*data_after)))

#下面数据是再加方向间隙过程中会变的位置
data_before_T2 = copy.deepcopy(data_before_T)
data_after_T2 = copy.deepcopy(data_after_T)

# 上一插补周期的运动为正（1）还是负（-1），初始值为0
motion_last = 0
motion_cur = 0
backlash_per_axis = [10000, 10000, 10000, 10000, 10000]
backlash_per_axis_left = [-1, -1, -1, -1, -1]

# 对于单个轴的数据
for i in range(len(data_before_T)):
    motion_last = 0
    motion_cur = 0
    backlash_per_axis_left[i] = -1

    for j in range(len(data_before_T[0])):

        # 记录上一次的运动方向
        motion_last = motion_cur

        if data_before_T2[i][j] > 0:
            motion_cur = 1

        elif data_before_T2[i][j] < 0:
            motion_cur = -1

        else:
            motion_cur = motion_last

        # 判断反向是否发生
        if motion_cur != motion_last and motion_last != 0:

            # 如果反向，激活left
            backlash_per_axis_left[i] = backlash_per_axis[i]

        # 在激活的这段时间内
        if backlash_per_axis_left[i] >= 0:

            # 这一段位移可以补上多少left
            backlash_per_axis_left[i] = backlash_per_axis_left[i] - abs(data_before_T2[i][j])

            if backlash_per_axis_left[i] >= 0:
                data_before_T2[i][j] = 0

            # 这个周期把反向间隙都补完了
            else:
                data_before_T2[i][j] = -1 * backlash_per_axis_left[i]

                # 把left关掉
                backlash_per_axis_left[i] = -1

# after补偿后
motion_last = 0
motion_cur = 0
backlash_per_axis = [10000, 10000, 10000, 10000, 10000]
backlash_per_axis_left = [-1, -1, -1, -1, -1]

for i in range(len(data_after_T)):
    motion_last = 0
    motion_cur = 0

    for j in range(len(data_after_T[0])):

        # 记录上一次的运动方向
        motion_last = motion_cur

        if data_after_T[i][j] > 0:
            motion_cur = 1

        elif data_after_T[i][j] < 0:
            motion_cur = -1

        else:
            motion_cur = motion_last

        # 判断反向是否发生
        if motion_cur != motion_last and motion_last != 0:

            # 如果反向，激活left
            backlash_per_axis_left[i] = backlash_per_axis[i]

        # 在激活的这段时间内
        if backlash_per_axis_left[i] >= 0:

            # 这一段位移可以补上多少left
            backlash_per_axis_left[i] = backlash_per_axis_left[i] - abs(data_after_T[i][j])

            if backlash_per_axis_left[i] >= 0:
                data_after_T[i][j] = 0

            # 这个周期把反向间隙都补完了
            else:
                data_after_T[i][j] = -1 * motion_cur * backlash_per_axis_left[i]

                # 把left关掉
                backlash_per_axis_left[i] = -1

# 速度，丝杠的速度，就是主动轴的速度
f_5_axes = [[], [], [], [], []]

for i in range(5):
    for j in range(len(data_after_T[0])):
        f_5_axes[i].append(60 * data_after_T2[i][j] / 2000)

plt.figure(figsize=(18, 9))
plt.subplot(211)
color = ['red', 'green', 'blue', 'red', 'green']
for j in range(3):
    plt.title('mm/min')
    plt.scatter([i for i in range(len(f_5_axes[j]))], f_5_axes[j], color=color[j], s=1)

plt.subplot(212)
for j in range(3, 5):
    plt.title('deg/min')
    plt.scatter([i for i in range(len(f_5_axes[j]))], f_5_axes[j], color=color[j], s=1)
plt.show()

# 加速度， 丝杠的加速度，从动的工作台的加速度无所谓是多少
acc_5_axes = [[], [], [], [], []]

for i in range(5):
    for j in range(1, len(data_after_T[0])):
        acc_5_axes[i].append((f_5_axes[i][j] - f_5_axes[i][j - 1]) / (2 / 1000 / 60) / 3600)

plt.figure(figsize=(18, 9))
plt.subplot(211)
for j in range(3):
    plt.title('mm/s^2')
    plt.scatter([i for i in range(len(acc_5_axes[j]))], acc_5_axes[j], color=color[j], s=1)

plt.subplot(212)
for j in range(3, 5):
    plt.title('deg/s^2')
    plt.scatter([i for i in range(len(acc_5_axes[j]))], acc_5_axes[j], color=color[j], s=1)
plt.show()

# 增量改为绝对位置
for i in range(5):

    for j in range(1, len(data_before_T[0])):
        data_before_T2[i][j] += data_before_T2[i][j - 1]
        data_before_T[i][j] += data_before_T[i][j - 1]
        data_after_T[i][j] += data_after_T[i][j - 1]

# 画画开始
# 各轴位置图
plt.figure(figsize=(18, 9))

for j in range(5):

    plt.subplot(231 + j)
    if j <= 2:
        plt.title("error[nm]--%daxis" %j)
    else:
        plt.title("error[udeg]--%daxis" %j)

    plt.scatter([i for i in range(len(data_before_T[0]))],
                [(data_before_T2[j][i] - data_before_T[j][i]) for i in range(len(data_before_T[4]))], color='red', s=10)
    plt.scatter([i for i in range(len(data_before_T[0]))],
                [data_after_T[j][i] - data_before_T[j][i] for i in range(len(data_before_T[4]))], color='green',
                marker='*', s=6)

    # if j <= 2:
    #     plt.title("[nm]--%daxis" %j)
    # else:
    #     plt.title("[udeg]--%daxis" %j)
    #
    # plt.scatter([i for i in range(len(data_before_T[0]))],
    #             data_before_T[j], color='blue', s=1)
    # plt.scatter([i for i in range(len(data_before_T[0]))],
    #             data_before_T2[j], color='red', s=10)
    # plt.scatter([i for i in range(len(data_before_T[0]))],
    #             data_after_T[j], color='green',
    #             marker='*', s=6)

plt.show()
