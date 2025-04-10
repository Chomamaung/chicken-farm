def config_flask_ser(app,com,b_rate):
    app.config['SERIAL_TIMEOUT'] = 0.2
    app.config['SERIAL_PORT'] = com
    app.config['SERIAL_BAUDRATE'] = b_rate
    app.config['SERIAL_BYTESIZE'] = 8
    app.config['SERIAL_PARITY'] = 'N'
    app.config['SERIAL_STOPBITS'] = 1
    return app
    
