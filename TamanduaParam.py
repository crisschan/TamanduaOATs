#encoding=utf-8
import TamanduaOATs
import csv
import sys
import os
'''
strOParamfile='C:\\Users\\C\Desktop\\ttt.csv'
taman=TamanduaParam(strOParamfile)
print taman.CalTaseCaseParam()
'''
class TamanduaParam(object):
    #the Origin Param csv file
    __mstrOParam=""
    #the result Param csv file
    #__mstrRParam=""
    #the script dir
    #__mstrScriptdir=""
    __listParam=[]

    def __init__(self,strOParam):
        self.__mstrOParam=strOParam
        self.__mstrScriptdir=sys.path[0]
    # return the a list[list] and a line is a tc
    def GetAllParam(self):
        csvOParamfile=file(self.__mstrOParam,'rb')
        reader = csv.reader(csvOParamfile)
        ilinestep=0
        for line in reader:
            if ilinestep==0:
                self.__listParam.append(line)
                iFactor = len(line)
                ilinestep=ilinestep+1
                
        #aline = reader.readlines()
        return self.__listParam
    def CalTaseCaseParam(self):
        aTC=[]
        #self.__mstrRParam = self.__mstrScriptdir+'\\RParam_.csv'
        csvOParamfile=file(self.__mstrOParam,'rb')
        #csvRParamfile=file(self.__mstrRParam,'wb')
        #save the level list
        listParamNumber=[]
        #save the totalparambnumber(all param number)
        iTotalParam=0
        #save the parambnumber(factor number)
        iFactor=0
        #save the orgin param 
        listOrginparam = []

        reader = csv.reader(csvOParamfile)
        ilinestep=0
        itemp=0
        for line in reader:
            
            if ilinestep==0:
                iFactor = len(line)
                
                while itemp<iFactor:
                    listParamNumber.append(0)
                    itemp=itemp+1
                ilinestep=ilinestep+1
            else:
                ifactorstep=0
                strTemp = line[ifactorstep]
                
                listOrginparam.append(line)
                while ifactorstep<iFactor:
                    strTemp=line[ifactorstep]
                    if  strTemp.strip():
                        listParamNumber[ifactorstep]=listParamNumber[ifactorstep]+1
                        iTotalParam=iTotalParam+1
                    ifactorstep=ifactorstep+1
        strRe=""
        for nAtom in listParamNumber:
            strRe=strRe+str(nAtom)
            strRe=strRe+','
        csvOParamfile.close() 
        strRe=strRe[:len(strRe)-1]
        strOATsResult = TamanduaOATs.OATs(iTotalParam,iFactor,strRe)
        listOATsResult = strOATsResult.split('\n')
        listATC=[]
        istepParamCol=0        
        for aOATs in listOATsResult:
            alineTC=[]
            if(len(aOATs)>3):
                aOATs= aOATs.strip()
                alistTC=aOATs.split(' ')
                istepParamCol=0
                for aElemtAtosTC in alistTC:
                    itemp=int(aElemtAtosTC)-1
                    alineTC.append(listOrginparam[itemp][istepParamCol])
                    istepParamCol=istepParamCol+1
                aTC.append(alineTC)
        return aTC
        


#------------------------------------------------
#strOParamfile='C:\\Users\\C\Desktop\\ttt.csv'
#taman=TamanduaParam(strOParamfile)
#print taman.GetAllParam()
#print taman.CalTaseCaseParam()
