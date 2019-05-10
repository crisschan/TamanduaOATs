#TamaduaOATs
## TamanduaOATs简介

生成正加实验的pyd（python库）程序（放到python下的dlls目录下）

## python调用方法如下：
  
  #encoding=utf-8 
  import TamanduaOATs
  print TamanduaOATs.OATs(7,2,'2,3') 

TamanduaParam输出按照正交计算出测试用了，结果是一个嵌套的list（放到python下的lib目录下） 使用法方法举例如下： 

  strOParamfile='C:\\Users\\C\Desktop\\ttt.csv' 
  taman=TamanduaParam(strOParamfile) 
  print taman.GetAllParam() 
  #print taman.CalTaseCaseParam()
