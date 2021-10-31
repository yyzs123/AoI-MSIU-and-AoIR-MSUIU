#import matplotlib
#matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.pyplot import MultipleLocator
import numpy as np
import os
import math
def Experiment1(ns, cs, alpha, ca):
    No = ['(a)', '(b)', '(c)', '(d)']
    plt.figure(figsize = (18, 4), dpi = 300)
    for i in range(0, len(alpha)):
        plt.subplot(1, 4, i + 1)
        Optimal_f = []
        Greedy_f = []
        Zerowait_f = []
        Periodical_f = []
        LCFS_f = []
        for j in range(0, len(ns)):
            with open(os.getcwd() + '\\Results\\' + str(ns[j]) + '_' + str(cs) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Optimal.txt', 'r') as f:
                Optimal_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns[j]) + '_' + str(cs) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Greedy.txt', 'r') as f:
                Greedy_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns[j]) + '_' + str(cs) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Zero-wait.txt', 'r') as f:
                Zerowait_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns[j]) + '_' + str(cs) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Periodical.txt', 'r') as f:
                Periodical_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns[j]) + '_' + str(cs) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_LCFS.txt', 'r') as f:
                LCFS_f.append(float(f.readline().split()[0]))

        Optimal_f = np.array(Optimal_f)
        Greedy_f = np.array(Greedy_f)
        Zerowait_f = np.array(Zerowait_f)
        Periodical_f = np.array(Periodical_f)
        LCFS_f = np.array(LCFS_f)
        Lower_optimal_f = (math.e - 1.0) / math.e * Optimal_f
        #optimal_4_3_f = 0.75 *Optimal_f

        #mn = min(Optimal_f.min(), Greedy_f.min(), Zerowait_f.min(), Periodical_f.min(), LCFS_f.min(), Lower_optimal_f.min())
        #mx = max(Optimal_f.max(), Greedy_f.max(), Zerowait_f.max(), Periodical_f.max(), LCFS_f.max(), Lower_optimal_f.max())
        #mn = min(Greedy_f.min(), Zerowait_f.min(), Periodical_f.min(), LCFS_f.min())
        #mx = max(Greedy_f.max(), Zerowait_f.max(), Periodical_f.max(), LCFS_f.max())

        plt.plot(ns, Optimal_f, 'k-.o', linewidth = 2, label = 'Optimal solution') #第1条曲线 Optimal
        plt.plot(ns, Lower_optimal_f, 'b-.x', linewidth = 2, label = 'Lower bound') #第2条曲线 lower_optimal
        plt.plot(ns, Greedy_f, 'r-.*', linewidth = 2, label = 'AoI-MSIU') #第3条曲线 AoI-MSIC
        plt.plot(ns, Zerowait_f, 'g-.*', linewidth = 2, label = 'Zero-wait policy') #第4条曲线 Zero-wait
        plt.plot(ns, Periodical_f, 'c-.^', linewidth = 2, label = 'Periodical policy') #第5条曲线 Periodical
        plt.plot(ns, LCFS_f, 'y-.s', linewidth = 2, label = 'LCFS') #第6条曲线 Lcfs
        #plt.plot(ns, optimal_4_3_f, 'm-.s', linewidth = 2, label = '0.75Optimal') #第6条曲线 Lcfs

        ax = plt.gca()
        ax.spines['top'].set_visible(False)  # 去掉上边框
        ax.spines['right'].set_visible(False)  # 去掉右边框

        
        plt.tick_params(labelsize = 10)
        plt.xticks(family = 'Times New Roman', fontweight = 'normal')
        plt.yticks(family = 'Times New Roman', fontweight = 'normal')
        plt.title(r'{} With $\alpha$ = {:.2f}'.format(No[i], alpha[i]), fontsize = 10, family = 'Times New Roman')
        plt.xlabel('The number of SNs', fontsize = 10, fontweight = 'normal') #x标签
        plt.ylabel('Overall Revenue', fontsize = 10, fontweight = 'normal') #y标签
        plt.xlim(5, 40)
        plt.ylim(0.0, 3500.0)
        plt.grid(linewidth = 2)

        font = {
            'family': 'Times New Roman',
            'size': 10
        }
        plt.legend(loc = 'upper left', prop = font)

        with open(os.getcwd() + '\\Results\\{:d}_{:.6f}_all_results'.format(ca, alpha[i]), 'w') as f:
            for x in Optimal_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Lower_optimal_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Greedy_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Zerowait_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Periodical_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in LCFS_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')

    plt.tight_layout() #去除pdf周围白边
    fig = plt.gcf()
    fig.savefig('1.png', format = 'png', dpi = 300)
    fig.savefig('1.pdf', format = 'pdf', dpi = 300)
             
def Experiment2(ns, cs, alpha, ca):
    No = ['(a)', '(b)', '(c)', '(d)']
    plt.figure(figsize = (18, 4), dpi = 300)
    for i in range(0, len(alpha)):
        #plt.figure()
        plt.subplot(1, 4, i + 1)
        Optimal_f = []
        Greedy_f = []
        Zerowait_f = []
        Periodical_f = []
        LCFS_f = []
        for j in range(0, len(cs)):
            with open(os.getcwd() + '\\Results\\' + str(ns) + '_' + str(cs[j]) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Optimal.txt', 'r') as f:
                Optimal_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns) + '_' + str(cs[j]) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Greedy.txt', 'r') as f:
                Greedy_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns) + '_' + str(cs[j]) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Zero-wait.txt', 'r') as f:
                Zerowait_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns) + '_' + str(cs[j]) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_Periodical.txt', 'r') as f:
                Periodical_f.append(float(f.readline().split()[0]))
            with open(os.getcwd() + '\\Results\\' + str(ns) + '_' + str(cs[j]) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha[i]) + '_LCFS.txt', 'r') as f:
                LCFS_f.append(float(f.readline().split()[0]))

        Optimal_f = np.array(Optimal_f)
        Greedy_f = np.array(Greedy_f)
        Zerowait_f = np.array(Zerowait_f)
        Periodical_f = np.array(Periodical_f)
        LCFS_f = np.array(LCFS_f)
        Lower_optimal_f = (math.e - 1.0) / math.e * Optimal_f

        #mn = min(Optimal_f.min(), Greedy_f.min(), Zerowait_f.min(), Periodical_f.min(), LCFS_f.min(), Lower_optimal_f.min())
        #mx = max(Optimal_f.max(), Greedy_f.max(), Zerowait_f.max(), Periodical_f.max(), LCFS_f.max(), Lower_optimal_f.max())
        #mn = min(Greedy_f.min(), Zerowait_f.min(), Periodical_f.min(), LCFS_f.min())
        #mx = max(Greedy_f.max(), Zerowait_f.max(), Periodical_f.max(), LCFS_f.max())

        index = cs
        total_width, n = 8, 6
        bar_width = total_width / n
        index = index - (total_width - bar_width) / 2
        plt.bar(index, Optimal_f, bar_width, color = 'k', label = 'Optimal solution') #第1条曲线 Optimal
        plt.bar(index + bar_width, Lower_optimal_f, bar_width, color = 'b', label = 'Lower bound') #第2条曲线 lower_optimal
        plt.bar(index + 2 * bar_width, height = Greedy_f, width = bar_width, color = 'r', label = 'AoI-MSIU') #第3条曲线 AoI-MSIC
        plt.bar(index + 3 * bar_width, height = Zerowait_f, width = bar_width, color = 'g', label = 'Zero-wait policy') #第4条曲线 Zero-wait
        plt.bar(index + 4 * bar_width, height = Periodical_f, width = bar_width, color = 'c', label = 'Periodical policy') #第5条曲线 Periodical
        plt.bar(index + 5 * bar_width, height = LCFS_f, width = bar_width, color = 'y', label = 'LCFS') #第6条曲线 Lcfs

        #plt.axis([cs[0], cs[-1], mn - 50.0, mx + 550.0]) #x,y轴范围
        #plt.xticks(index + 5 * bar_width / 2, cs, fontsize = 9, family = 'Times New Roman')
        ax = plt.gca()
        ax.spines['top'].set_visible(False)  # 去掉上边框
        ax.spines['right'].set_visible(False)  # 去掉右边框

        plt.tick_params(labelsize = 10)
        plt.xticks(cs, family = 'Times New Roman', fontweight = 'normal')
        plt.yticks(family = 'Times New Roman', fontweight = 'normal')
        plt.title(r'{} With $\alpha$ = {:.2f}'.format(No[i], alpha[i]), fontsize = 10, family = 'Times New Roman')
        plt.xlabel('The number of status', fontsize = 10, fontweight = 'normal') #x标签
        plt.ylabel('Overall Revenue', fontsize = 10, fontweight = 'normal') #y标签
        plt.ylim(0, 4500.0)
        plt.grid(linewidth = 2)
        font = {
            'family': 'Times New Roman',
            'size': 10
        }
        plt.legend(loc = 'upper left', prop = font)
        

        #y_major_locator=MultipleLocator(500)
        #ax = plt.gca()
        #ax.yaxis.set_major_locator(y_major_locator)

        with open(os.getcwd() + '\\Results\\{:d}_{:.6f}_all_results'.format(ca, alpha[i]), 'w') as f:
            for x in Optimal_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Lower_optimal_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Greedy_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Zerowait_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in Periodical_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')
            for x in LCFS_f:
                f.write('{:.2f} '.format(x))
            f.write('\n')

    plt.tight_layout() #去除pdf周围白边
    fig = plt.gcf()
    fig.savefig('2.png', format = 'png', dpi = 300)
    fig.savefig('2.pdf', format = 'pdf', dpi = 300)


#def Experiment2(ns, cs, alpha):


if __name__ == '__main__':
    Experiment1(np.arange(5, 41, 5, dtype = int), 40, np.array([0.5, 1.0, 1.5, 2.0]), 50)
    Experiment2(80, np.arange(10, 81, 10, dtype = int), np.array([0.5, 1.0, 1.5, 2.0]), 50)

