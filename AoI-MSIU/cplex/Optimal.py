import os
import argparse
import time
from amplpy import AMPL
# Create an AMPL instance

def args_parser():
    parser = argparse.ArgumentParser()
    # federated arguments
    parser.add_argument('--ns', type=int, help="SN size")
    parser.add_argument('--cs', type=int, help="Content size")
    parser.add_argument('--ca', type=int, help="Total case")
    parser.add_argument('--alpha', type=float, help="Alpha")
    args = parser.parse_args()
    return args


if __name__ == '__main__':
    print(os.getcwd())
    print(os.path.dirname(os.getcwd()))
    args = args_parser()
    ns, cs, ca, alpha = args.ns, args.cs, args.ca, args.alpha

    pwd = os.getcwd()
    dirpath = os.path.dirname(pwd) + '\\..\\Data\\' + str(ns) + '_' + str(cs) + '_' + str(ca) + '\\'
    
    sumf = .0
    # Interpret the two files
    for i in range(1, ca + 1):
        ampl = AMPL()
        ampl.read('optimal.mod')
        ampl.readData(dirpath + str(i) + '_ampl.dat')
        p_alpha = ampl.getParameter('alpha')
        p_alpha.setValues([alpha])
        # Solve
        ampl.solve()

        f = ampl.getObjective('revenue')
        sumf += f.value()
        
    with open(os.path.dirname(pwd) + '\\Results\\' + str(ns) + '_' + str(cs) + '_' + str(ca) + '_' + '{:.6f}'.format(alpha) + '_Optimal.txt', 'w') as file:
        file.write('{} {}\n'.format(round(sumf / ca, 2), round(time.time())))
    