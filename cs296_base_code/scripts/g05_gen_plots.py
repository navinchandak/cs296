#!/usr/bin/env python

import math
import numpy as ny
import pylab

data = ny.genfromtxt('./data/lab05_g05_data.csv', delimiter=',', names=['rerun','iteration','step','collision','velocity','position','loop'])

step_mod=[]
collision_mod=[]
velocity_mod=[]
position_mod=[]
loop_mod=[]
iteration_mod=[]

for i in range(100):
	sum1=0	
	sum2=0
	sum3=0
	sum4=0
	sum5=0
	for j in range(100):
		sum1 = sum1 + data['step'][i + 100*j];
		sum2 = sum2 + data['collision'][i + 100*j];
		sum3 = sum3 + data['velocity'][i + 100*j];
		sum4 = sum4 + data['position'][i + 100*j];
		sum5 = sum5 + data['loop'][i + 100*j]
	step_mod.append(sum1/100)
	collision_mod.append(sum2/100)
	velocity_mod.append(sum3/100)
	position_mod.append(sum4/100)
	loop_mod.append(sum5/100)
	iteration_mod.append(i + 1)


step_mod_r=[]
collision_mod_r=[]
velocity_mod_r=[]
position_mod_r=[]
loop_mod_r=[]
rerun_mod=[]

for i in range(100):
	sum6=0	
	sum7=0
	sum8=0
	sum9=0
	sum10=0
	for j in range(100):
		sum6 = sum6 + data['step'][100*i + j];
		sum7 = sum7 + data['collision'][100*i + j];
		sum8 = sum8 + data['velocity'][100*i + j];
		sum9 = sum9 + data['position'][100*i + j];
		sum10 = sum10 + data['loop'][100*i + j];
	step_mod_r.append(sum6/100)
	collision_mod_r.append(sum7/100)
	velocity_mod_r.append(sum8/100)
	position_mod_r.append(sum9/100)
	loop_mod_r.append(sum10/100)
	rerun_mod.append(i + 1)


deviation=[]
for i in range(100):
	sum11=0
	for j in range(100):
		sum11 = sum11 + (data['step'][i + 100*j] - step_mod[i])**2
	deviation.append(math.sqrt(sum11/99))


step_mod_29=[]
for j in range(100):
	step_mod_29.append(data['step'][28 + 100*j])



pylab.figure(1)
pylab.plot(iteration_mod, step_mod, color='r', marker='.', linestyle=':', label='average step time')
pylab.hold('on')
pylab.plot(iteration_mod, loop_mod, color='g', marker='.', linestyle=':', label='average loop time')
pylab.axis([0,100,0,40])
pylab.xlabel('Iteration value')
pylab.ylabel('Average steptime and loop time over reruns(in ms)')
pylab.title('Plot01')
pylab.legend()
pylab.savefig('./plots/plot01.png')
pylab.show()


pylab.figure(2)
pylab.plot(iteration_mod, step_mod, color='k', marker='.', linestyle=':', label='average step time')
pylab.hold('on')
pylab.plot(iteration_mod, collision_mod, color='g', marker='.', linestyle=':', label='average collision time')
pylab.hold('on')
pylab.plot(iteration_mod, velocity_mod, color='b', marker='.', linestyle=':', label='average velocity updation time')
pylab.hold('on')
pylab.plot(iteration_mod, position_mod, color='r', marker='.', linestyle=':', label='average position updation time')
pylab.xlabel('Iteration value')
pylab.ylabel('Averaged values over all reruns(in ms)')
pylab.title('Plot02')
pylab.legend()
pylab.savefig('./plots/plot02.png')
pylab.show()


pylab.figure(3)
pylab.plot(rerun_mod, step_mod_r, color='r', marker='.', linestyle=':', label='average step time')
pylab.hold('on')
pylab.plot(rerun_mod, loop_mod_r, color='g', marker='.', linestyle=':', label='average loop time')
pylab.axis([0,100,0,40])
pylab.xlabel('Rerun number')
pylab.ylabel('Average steptime and loop time over all iterations(in ms)')
pylab.title('Plot03')
pylab.legend()
pylab.savefig('./plots/plot03.png')
pylab.show()


pylab.figure(4)
pylab.plot(rerun_mod, step_mod_r, color='k', marker='.', linestyle=':', label='average step time')
pylab.hold('on')
pylab.plot(rerun_mod, collision_mod_r, color='g', marker='.', linestyle=':', label='average collision time')
pylab.hold('on')
pylab.plot(rerun_mod, velocity_mod_r, color='b', marker='.', linestyle=':', label='average velocity updation time')
pylab.hold('on')
pylab.plot(rerun_mod, position_mod_r, color='r', marker='.', linestyle=':', label='average position updation time')
pylab.axis([0,100,0,2])
pylab.xlabel('Rerun number')
pylab.ylabel('Averaged values over all iterations(in ms)')
pylab.title('Plot04')
pylab.legend()
pylab.savefig('./plots/plot04.png')
pylab.show()


pylab.figure(5)
pylab.errorbar(iteration_mod, step_mod, yerr=deviation, color='r', marker='.', linestyle=':', label='average step time with y errorbars')
pylab.xlabel('Iteration value')
pylab.ylabel('Average steptime over all reruns with y errorbars(in ms)')
pylab.title('Plot05')
pylab.legend()
pylab.savefig('./plots/plot05.png')
pylab.show()


pylab.figure(6)
a, b, c = pylab.hist(step_mod_29, bins=20, histtype='bar', label='frequency plot')
cumu = ny.cumsum(a)
pylab.plot(b[:-1], cumu, label='Cumulative Frequency')
pylab.xlabel('Step time(in ms)')
pylab.ylabel('Frequency')
pylab.title('Plot06')
pylab.legend()
pylab.savefig('./plots/plot06.png')
pylab.show()
