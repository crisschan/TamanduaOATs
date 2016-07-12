import TamanduaParam

strfile = 'C:\\Users\\C\\Desktop\\ttt.csv'
tman=TamanduaParam.TamanduaParam(strfile)

#print tman.GetAllParam()

aa = tman.CalTaseCaseParam()
bb = tman.GetAllParam()

f=open('C:\\Users\\C\\Desktop\\11.txt','w')
print bb
print '--------------------'
print aa
for aline in aa:
	k=' '.join([str(aelem) for aelem in aline])
	f.writelines(k+'\n')
f.close()
