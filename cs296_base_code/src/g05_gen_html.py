import re
texfile=open("doc/g05_prof_report.tex",'r')
latex_str=texfile.read()
htmlfile=open("doc/g05_lab09_report.html",'w')
html_str=latex_str
def printhtml():
	print"------------------------------"
	print html_str[1:2000]
	print"--------------------------------"
def change():
	global html_str
	print latex_str[1:1500]
	html_str=r"<html><link rel='stylesheet' href='style.css' type='text/css'>"+html_str
	html_str=re.sub(r"\\begin\{document\}([\w\s\d\\\/,.\(\)\{\}<>\[\]\=\_\'\%\*\$\-\:\`\?\;\+\!]*)\\end\{document}",r"<body> \1 </body></html> ",html_str)
	html_str=re.sub(r"\\subsection\{([\w\s\(\),.]*)\}",r"<div class='subsection'> \1 </div> ",html_str)
	printhtml()
	html_str=re.sub(r"\\section\{([\w\s\(\),.]*)\}",r"<div class='section'> \1 </div> ",html_str)
	html_str=re.sub(r"\\begin\{enumerate\}([\w\s\\,.\(\)]*)\\end\{enumerate}",r"<ul> \1 </ul> ",html_str)
	html_str=re.sub(r"\\begin\{itemize\}([\w\s\d\\\/,.\(\)\{\}<>\[\]\=\_\'\%\*\$\-\:\`\?\;\+\!]*?)\\end\{itemize}",r"<ol> \1 </ol> ",html_str)
	html_str=re.sub(r"\\includegraphics[\w\s=\d\[\],]*\{doc\/([\w\d\/\_.]*)\}",r"<img src='\1'> </img> ",html_str)
	html_str=re.sub(r"\\item",r"<li>",html_str)
	html_str=re.sub(r"\\\*",r"</br>",html_str)
	html_str=re.sub(r"\\%",r"%",html_str)
	html_str=re.sub(r"\$\\mu\$",r"&Mu;",html_str)
	html_str=re.sub(r"\.eps",r".png",html_str)
	html_str=re.sub(r"\\.*",r"",html_str)
	htmlfile.write(html_str)
	printhtml()
	

change()
