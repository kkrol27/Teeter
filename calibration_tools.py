import csv
import numpy as np
import matplotlib.pyplot as plt


raw_data_array = None
data_arr = np.loadtxt('imucal.csv', delimiter=',')
print(np.shape(data_arr))

ax_data = data_arr[:, 0]
ay_data = data_arr[:, 1]
az_data = data_arr[:, 2]
gx_data = data_arr[:, 3]
gy_data = data_arr[:, 4]
gz_data = data_arr[:, 5]

ax_mean, ax_std = np.mean(ax_data), np.std(ax_data)
ay_mean, ay_std = np.mean(ay_data), np.std(ay_data)
az_mean, az_std = np.mean(az_data), np.std(az_data)

gx_mean, gx_std = np.mean(gx_data), np.std(gx_data)
gy_mean, gy_std = np.mean(gy_data), np.std(gy_data)
gz_mean, gz_std = np.mean(gz_data), np.std(gz_data)

mean_arr = np.array([ax_mean, ay_mean, az_mean, gx_mean, gy_mean, gz_mean])
std_arr = np.array([ax_std, ay_std, az_std, gx_std, gy_std, gz_std])

print(mean_arr)
print(std_arr)
