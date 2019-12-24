# QualcommSerialportTool
QualcommSerialportTool

This tool is designed to write SN Serial Number,WIFI mac address or Bluetooth hardware address to Android Development <br>  Board which is based on the Qualcomm SOC.<br>  
Follonging comes the details instructions to write these Serial Numbers:<br>  

AT+SYSCMD=lserialn******** SN Serial Number Instruction(***** refers to specific serial number)<br>  
AT+SYSCMD=readsn Read SN Serial Number<br>  
AT+LCTSN=1,12,"*************" Write Wifi mac address instruction(***** is specific wifi mac address,serial number must be only 12 characters and also must be hexadecimal)<br>  
AT+LCTSN=1,10,"*************" BlueTooth Serial number<br>  
AT+SIMSWAPEN=1,1 Sim1 support hot plug<br>  
AT+SIMSWAPEN=0,1 Sim1 doesn't support hot plug<br>  
AT+SIMSWAPEN=1,2 Sim2 support hot plug<br>  
AT+SIMSWAPEN=0,2 Sim2 doesn't support hot plug<br>  
AT+SIMSWAPEN? consult sim1 and sim2 hot plug status<br>  



                Qualcomm SOC ONLY!<br>  
