# QualcommSerialportTool
QualcommSerialportTool
This tool is designed to write SN Serial Number,WIFI mac address or Bluetooth hardware address to Android Development Board which is based on the Qualcomm SOC.
Follonging comes the details instructions to write these Serial Numbers:

AT+SYSCMD=lserialn******** SN Serial Number Instruction(***** refers to specific serial number)
AT+SYSCMD=readsn Read SN Serial Number
AT+LCTSN=1,12,"*************" Write Wifi mac address instruction(***** is specific wifi mac address,serial number must be only 12 characters and also must be hexadecimal)
AT+LCTSN=1,10,"*************" BlueTooth Serial number
AT+SIMSWAPEN=1,1 Sim1 support hot plug
AT+SIMSWAPEN=0,1 Sim1 doesn't support hot plug
AT+SIMSWAPEN=1,2 Sim2 support hot plug
AT+SIMSWAPEN=0,2 Sim2 doesn't support hot plug
AT+SIMSWAPEN? consult sim1 and sim2 hot plug status



                Qualcomm SOC ONLY!
