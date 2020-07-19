IP=10.0.0.2

.PHONY: header
header:
	sopc-create-header-files "base_hps.sopcinfo" --single header/hps_0.h --module hps_0

.PHONY:rbf
rbf:
	quartus_cpf -c -o bitstream_compression=on ./output_files/robot.sof ./output_files/robot.rbf

.PHONY:upload
upload:
	scp output_files/output_file.rbf root@$(IP):~/robot/robot.rbf

.PHONY:upload
dtbo_upload:
	scp output_files/robot.dtbo root@$(IP):~/robot/robot.dtbo
