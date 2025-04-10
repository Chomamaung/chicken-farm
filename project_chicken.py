from flask import Flask, request
from text_line import gettext

from linebot import LineBotApi
from linebot.models import TextSendMessage as send_text

from flask_serial import Serial
from config_flask_serial import config_flask_ser

tp = ""
rtp = 0


channel_access_token = "oDKy6edvexiJeuSydHjWKYQChBrcgr9B+7njhvRk4n4DbaNjQ9iEzY9yt4aq15PHkh4NLuo89+2CHS/sp7NgkgotSv2K2rz4TmAgDkiG9/e/LP8ypDSmPia0VKRyybX+fVPQiHefewETjrAoP5NAEQdB04t89/1O/w1cDnyilFU="
line_send = LineBotApi(channel_access_token).reply_message

app = Flask(__name__)
ser = Serial(config_flask_ser(app,'COM2',9600))

@app.route("/",methods=["GET","POST"])
def home():
    global tp,sm
    text,reply_token = gettext(request)
    if (text != ""):
        print(text)
        if (text == "ให้น้ำไก่"):
            ser.on_send("a")  
            line_send(reply_token,send_text(text="ให้น้ำไก่เรียบร้อย"))
            
        if (text == "ให้อาหารไก่"):
            ser.on_send("b")
            line_send(reply_token,send_text(text="ให้อาหารไก่เรียบร้อย"))
            
        if (text == "เปิดน้ำลดอุณหภูมิ"):
            ser.on_send("c")        
            line_send(reply_token,send_text(text="เปิดน้ำลดอุณหภูมิเรียบร้อย"))
            
        if (text == "ปิดน้ำลดอุณหภูมิ"):
            ser.on_send("d")
            line_send(reply_token,send_text(text="ปิดน้ำลดอุณหภูมิเรียบร้อย"))
            
        if (text == "ขอทราบอุณหภูมิ"):
            if (tp != ""):
                rtp = int(tp)
                if(rtp >= 34):
                    text_out = "ขณะนี้อุณหภูมิ " + str(tp) + " องศาเซลเซียส" + "\nควรเปิดน้ำลดอุณหภูมิ"
                    line_send(reply_token,send_text(text=text_out))
                else:
                    text_out = "ขณะนี้อุณหภูมิ " + str(tp) + " องศาเซลเซียส"
                    line_send(reply_token,send_text(text=text_out))
            
    return "Hello LINE"

@ser.on_message()
def ser_read(textin):
    global tp
    temp = textin.decode().splitlines()[0]
    if temp.startswith("tp"):
        tp = temp.strip("tp") 

app.run()
