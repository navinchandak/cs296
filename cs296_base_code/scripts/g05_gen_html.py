import re
texfile=open("doc/itslatex.tex",'r')
latex_str=texfile.read()
htmlfile=open("doc/g05_report.html",'w')
html_str=latex_str
def reference():
	bibfile=open("doc/mybib.bib",'r')
	bib_str=bibfile.read()
	temp_bib=re.findall(r"\@[\w]*\{[\s\S]*?[\s]\}",bib_str)
	ref_str="<ul>"
	for temp in temp_bib:
		sections_temp=re.search(r"\@misc\{(.*?),[\s\S]*?\{([\s\S]*?)\}[\s\S]*?url\{([\s\S]*?)\}[\s\S]*?[\s]\}",temp)
		if(sections_temp):
			ref_str+="<li><a name='#"+sections_temp.group(1)+"'></a> "+sections_temp.group(2)+" <a href='"+sections_temp.group(3)+"'>Link</a>"	
		else:
			sections_temp=re.search(r"\@BOOK\{(.*?),[\s\S]*?\"([\s\S]*?)\"[\s\S]*?\"([\s\S]*?)\"[\s\S]*?[\s]\}",temp)
			ref_str+="<li><a name='#"+sections_temp.group(1)+"'></a>"+sections_temp.group(3)+" by "+sections_temp.group(2)
	return ref_str

def printhtml():
	print (html_str[0:700])
	print("----------------------------------------------------")
def change():
	global html_str
	sections_temp=re.findall(r"\\section\{([\w\s\(\),.]*)\}",html_str)	
	contents_str="<a name='top'>Contents</a></br>"
	contents_str+=r"<div id='contents'> <ol>"
	for section_temp in sections_temp:
		section=re.sub(r"\\section\{([\w\s\(\),.]*)\}",r"\1",section_temp);
		contents_str+= r"<li><a href='#"+ re.sub(r"[^\w]",'',section)+ r"'> "+section+ r"</a></li>"
	contents_str+=r"</ol>"
	reference_string="</ol><div class='section'>References </div>"+reference()

	html_str=r"<link rel='stylesheet' href='style.css' type='text/css'>"+html_str
	html_str=re.sub(r"\~\\cite\{([\s\S]*?)\}",r"[<a href='#\1'>\1</a>]",html_str)
	html_str=re.sub(r"\\begin\{document\}([\S\s]*)\\end\{document}",r"<html> <title> Report </title> <body>"+contents_str+r" <ol> \1 </ol>"+reference_string+r"</body></html> ",html_str)

	html_str=re.sub(r"\\subsection\{([\S\s]*?)\}",r"<div class='subsection'><li>\1 </div> ",html_str)
	html_str=re.sub(r"\\section\{([\s\S]*?)\}",r"</ol><div class='section'> <a name='\1'> \1 </a><div class='top'> <a href='#top'>Back to top</a></div> </div><ol> ",html_str)
	print(html_str)
	html_str=re.sub(r"\<a name\=\'([\s\S]*?)\'\>",lambda m: "<a name='"+re.sub(r'[^\w]', '', m.group(1))+"'>",html_str)	
	html_str=re.sub(r"\\begin\{enumerate\}([\S\s]*?)\\end\{enumerate}",r"<ul> \1 </ul> ",html_str)
	html_str=re.sub(r"\\begin\{itemize\}([\S\s]*?)\\end\{itemize}",r"<ol>\1</ol> ",html_str)
	scaleF=43
	html_str=re.sub(r"\\includegraphics\[width=([\d.]*)cm\, height=([\d.]*)cm\]\{doc\/([\w\d\/\_.]*)\}",lambda m: r"<img style='width:"+str(float(m.group(1))*scaleF)+r";height:"+str(float(m.group(2))*scaleF)+r"px' src='"+m.group(3)+"'> </img> ",html_str)
	html_str=re.sub(r"\\includegraphics\[width=([\d.]*)cm\]\{doc\/([\w\d\/\_.]*)\}",lambda m: r"<img style='width:"+str(float(m.group(1))*scaleF)+r"' src='"+m.group(2)+"'> </img> ",html_str)
	html_str=re.sub(r"\\includegraphics\[width=([\d.]*)cm\]\{plots\/([\w\d\/\_.]*)\}",lambda m: r"<img style='width:"+str(float(m.group(1))*scaleF)+r"' src='../plots/"+m.group(2)+"'> </img> ",html_str)
	html_str=re.sub(r"\\includegraphics\[width=([\d.]*)cm\, height=([\d.]*)cm\]\{plots\/([\w\d\/\_.]*)\}",lambda m: r"<img style='width:"+str(float(m.group(1))*scaleF)+r";height:"+str(float(m.group(2))*scaleF)+r"px' src='../plots/"+m.group(3)+"'> </img> ",html_str)
	html_str=re.sub(r"\\item",r"<li>",html_str)
	html_str=re.sub(r"\\\*",r"</br>",html_str)
	html_str=re.sub(r"\\%",r"%",html_str)
	html_str=re.sub(r"\$\\mu\$",r"&#956;",html_str)
	html_str=re.sub(r"\\newline",r"</br>",html_str)
	html_str=re.sub(r"\\author\{[\S\s]*?\}",r"",html_str)
	html_str=re.sub(r"\\.*",r"",html_str)
	htmlfile.write(html_str)

change()
