#!/usr/bin/env python3
import matplotlib.pyplot as plt
import numpy as np

x_values = [10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000]
mean_times = [0.0078, 0.0078, 0.0080, 0.0097, 0.0251, 0.1707, 1.626, 16.134]
std_devs = [0.0020, 0.0020, 0.0019, 0.0019, 0.0031, 0.0095, 0.054, 0.511]

plt.figure(figsize=(10, 6))

plt.errorbar(x_values, mean_times, yerr=std_devs,
             fmt='o-', capsize=6, capthick=1.5,
             markersize=8, linewidth=2, color='steelblue',
             ecolor='lightcoral', elinewidth=1.5,
             label='Измерения')

plt.xscale('log')
plt.yscale('log')
plt.xlabel('Количество итераций (-x)', fontsize=12)
plt.ylabel('Время выполнения (секунды)', fontsize=12)
plt.title('Зависимость времени выполнения от количества итераций', fontsize=14)

x_theory = np.logspace(1, 8, 100)
plt.plot(x_theory, 1e-7 * x_theory, '--', alpha=0.5, linewidth=1, label='O(n)')
plt.plot(x_theory, 1e-9 * x_theory**2, '--', alpha=0.5, linewidth=1, label='O(n²)')
plt.plot(x_theory, 1e-12 * x_theory**3, '--', alpha=0.5, linewidth=1, label='O(n³)')

plt.grid(True, alpha=0.3, which='both')
plt.legend()

plt.savefig('hyperfine_dumps/hyperfine_plot.png', dpi=300, bbox_inches='tight')
