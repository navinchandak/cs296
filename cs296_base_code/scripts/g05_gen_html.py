import re
texfile=open("doc/g05_prof_report.tex",'r')
latex_str=texfile.read()
htmlfile=open("doc/g05_lab09_report.html",'w')
html_str=latex_str
def printhtml():
	print (html_str[1:2000])
def change():
	global html_str
	sections_temp=re.findall(r"\\section\{([\w\s\(\),.]*)\}",html_str)	
	contents_str="<a name='top'>Contents</a></br>"
	contents_str+=r"<div id='contents'> <ol>"
	for section_temp in sections_temp:
		section=re.sub(r"\\section\{([\w\s\(\),.]*)\}",r"\1",section_temp);
		contents_str+= r"<li><a href='#"+ re.sub(r"[^\w]",'',section)+ r"'> "+section+ r"</a></li>"
	contents_str+=r"</ol>"

	html_str=r"<link rel='stylesheet' href='style.css' type='text/css'>"+html_str
	html_str=re.sub(r"\\begin\{document\}([\w\s\d\\\/,.\(\)\{\}<>\[\]\=\_\'\%\*\$\-\:\`\?\;\+\!]*)\\end\{document}",r"<html> <title> Report </title> <body>"+contents_str+r" <ol> \1 </ol></body></html> ",html_str)

	html_str=re.sub(r"\\subsection\{([\w\s\(\),.]*)\}",r"<div class='subsection'><li>\1 </div> ",html_str)
	html_str=re.sub(r"\\section\{([\w\s\(\),.]*)\}",r"</ol><div class='section'> <a name='\1'> \1 </a><div class='top'> <a href='#top'>Back to top</a></div> </div><ol> ",html_str)
	html_str=re.sub(r"\<a name\=\'([^<]*?)\'\>",lambda m: "<a name='"+re.sub(r'[^\w]', '', m.group(1))+"'>",html_str)	
	html_str=re.sub(r"\\begin\{enumerate\}([\w\s\\,.\(\)]*)\\end\{enumerate}",r"<ul> \1 </ul> ",html_str)
	html_str=re.sub(r"\\begin\{itemize\}([\w\s\d\\\/,.\(\)\{\}<>\[\]\=\_\'\%\*\$\-\:\`\?\;\+\!]*?)\\end\{itemize}",r"<ol>\1</ol> ",html_str)
	html_str=re.sub(r"\\includegraphics[\w\s=\d\[\],]*\{doc\/([\w\d\/\_.]*)\}",r"<img src='\1'> </img> ",html_str)
	html_str=re.sub(r"\\item",r"<li>",html_str)
	html_str=re.sub(r"\\\*",r"</br>",html_str)
	html_str=re.sub(r"\\%",r"%",html_str)
	html_str=re.sub(r"\$\\mu\$",r"&#956;",html_str)
	html_str=re.sub(r"\.eps",r".png",html_str)
	html_str=re.sub(r"(g05_)(plot0[\d].png)",r"../plots/\1lab09_\2",html_str)
	html_str=re.sub(r"\\.*",r"",html_str)
	htmlfile.write(html_str)

change()
