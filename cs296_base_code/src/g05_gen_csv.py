import subprocess
import re
csv_file=open("./data/lab05_g05_data.csv",'w')
def gen_csv():
	last_index=100
	x=last_index+1
	for i in range(1,x):
		for j in range(1,x):
			arg=str(j)
			opt=subprocess.Popen(["./mybins/cs296_exe_05",arg],stdout=subprocess.PIPE).communicate()[0]
			opt=opt.split('\n')
			p=str(i)+","+str(j)+","
			for k in range(1,len(opt)) :
				match=re.search("[\d.]+",opt[k])
				if match:
					p+=match.group()+","
			csv_file.write((p[0:-1]+"\n"))

gen_csv()
