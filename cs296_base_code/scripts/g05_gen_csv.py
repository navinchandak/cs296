import subprocess
import re
csv_file=open("./data/lab05_g05_data.csv",'w')
def gen_csv():
	last_index=100
	x=last_index+1
	for i in range(1,x):
		for j in range(1,x):
			arg=str(j)
			opt=subprocess.Popen(["./bin/cs296_base",arg],stdout=subprocess.PIPE).communicate()[0]
			opt=opt.decode("utf-8")
			opt=opt.split('\n')
			p=str(i)+","+str(j)+","
			for k in range(1,len(opt)) :
				match=re.search("[\d.]+",opt[k])
				if match:
					p+=match.group()+","
			to_write=p[0:-1]+"\n"
			csv_file.write(to_write)

gen_csv()
