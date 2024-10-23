
filename = "5x7.bdf"
fontname = filename.split(".")[0]

f = open(filename, "r")
chardict = {}
curchar = None;

for line in f:
    line = line.strip();
    if ("FONTBOUNDINGBOX" in line):
        fontheight = line.split()[2]
        fontwidth = line.split()[1]
    if ("ENCODING" in line) and ("CHARSET_ENCODING" not in line):
        curchar = line.split()[1]
        if int(curchar) not in range(0, 127):
            break
        chardict[curchar] = ""
    if len(line) == 2:
        chardict[curchar] += "0x" + line + ", "

filler = "0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00"
size = 0
bitmap = ""

bitmap += "const uint8_t font_"+fontname+"[] = {\n"
for x in range(32, 126):
    size += 1
    c = str(x)
    if c in chardict.keys():
        bitmap += chardict[c] + "/*"+chr(x)+ "*/ \n"
    else:
        bitmap += filler
        
bitmap += "0x00 };\r\n\n"
bitmap += "const char* font_"+fontname+'_name = "'+fontname+'";\n'
bitmap += "const unsigned int font_"+fontname+"_glyphnum = "+str(size)+";\n"
bitmap += "const unsigned int font_"+fontname+"_arraylength = "+str(size*int(fontheight))+";\n"
bitmap += "const unsigned int font_"+fontname+"_width = "+fontwidth+";\n"
bitmap += "const unsigned int font_"+fontname+"_height = "+fontheight+";"

size = 0;

print(bitmap)
