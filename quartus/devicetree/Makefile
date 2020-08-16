IP=10.0.0.2

all: dtb

.PHONY:dtb
dtb:
	dtc -O dtb -o socfpga_cy5.dtb socfpga_cy5.dts

.PHONY:upload_dtb
upload_dtb:
	scp socfpga_cy5.dtb root@$(IP):/mnt/socfpga.dtb

