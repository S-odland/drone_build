# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c"
				   "imu.c"
				   "i2c_custom.c"
				   "custom_wifi.c"
				   "websocket.c")

set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()
