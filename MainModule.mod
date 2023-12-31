MODULE MainModule
	VAR bool cmd:=FALSE;
	VAR byte c:=0;
	PROC main()
		MoveJ [[230.47,31.63,244.70],[0.00873776,-0.0468926,0.998859,-0.00232724],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]], v1000, z50, tool0;
        gripper;
		WHILE TRUE DO
			WaitDI DI10_14, 1;
			c := 0;
			cmd := TestDI(DI10_15);
			c := BitOr(c,DI10_9);
			c := BitOr(c,BitLSh(DI10_10,1));
			c := BitOr(c,BitLSh(DI10_11,2));
			c := BitOr(c,BitLSh(DI10_12,3));
			c := BitOr(c,BitLSh(DI10_13,4));
			IF c = 0 MoveJ [[230.47,31.63,244.70],[0.00873776,-0.0468926,0.998859,-0.00232724],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]], v1000, z50, tool0;
			IF c = 1 input [[409.83,-122.90,204.41],[4.71202E-05,0.0466081,-0.998913,-9.85999E-05],[-1,0,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 2 input [[463.13,-117.88,202.24],[0.000249299,0.0466836,-0.99891,-0.000165769],[-1,0,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 3 input [[534.97,-112.06,205.18],[0.00875883,-0.046869,0.99886,-0.00231084],[-1,-1,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 4 input [[436.01,-180.64,201.69],[0.00875854,-0.0468702,0.99886,-0.00230994],[-1,0,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 5 input [[493.07,-179.27,205.69],[0.00875908,-0.0468696,0.99886,-0.00230949],[-1,0,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 6 input [[387.89,150.11,200.56],[0.00876899,-0.0469093,0.998858,-0.00232436],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 7 input [[443.63,155.36,201.53],[0.0087673,-0.0469108,0.998858,-0.00232632],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 8 input [[508.58,161.56,205.76],[0.00865144,-0.047048,0.998852,-0.00235975],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 9 input [[415.42,215.09,204.47],[0.00876802,-0.0469082,0.998858,-0.00232432],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 10 input [[472.40,218.43,202.47],[0.00876684,-0.0469052,0.998858,-0.0023247],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 11 input [[423.73,-34.82,205.54],[0.00887174,-0.0468345,0.99886,-0.00252151],[-1,-1,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 12 input [[412.56,20.42,209.45],[0.0114464,-0.0468869,0.998832,-0.00246876],[0,-1,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 13 input [[407.20,77.24,210.10],[0.0114478,-0.0468851,0.998832,-0.00246687],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 14 input [[472.15,-32.17,205.84],[0.00839789,-0.0468465,0.998864,-0.00222483],[-1,-1,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 15 input [[468.30,25.67,210.71],[0.0114483,-0.0468908,0.998831,-0.00246761],[0,-1,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 16 input [[466.82,83.86,211.46],[0.0114467,-0.0468859,0.998832,-0.00246836],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 17 input [[528.89,-26.84,206.78],[0.00839814,-0.0468429,0.998864,-0.00222602],[-1,-1,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 18 input [[524.20,30.89,204.98],[0.0114457,-0.0468833,0.998832,-0.0024681],[0,-1,-1,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
			IF c = 19 input [[518.63,88.04,212.64],[0.0114502,-0.0468843,0.998832,-0.00246671],[0,-1,0,0],[9E+09,9E+09,9E+09,9E+09,9E+09,9E+09]];
		ENDWHILE
	ENDPROC
	PROC input(robtarget position)
		MoveJ Offs(position,0,0,100), v1000, fine, tool0;
		MoveJ position, v1000, fine, tool0;
		gripper;
		MoveJ Offs(position,0,0,100), v1000, fine, tool0;
	ENDPROC
	PROC gripper()
		IF cmd THEN
			Reset doGripOpen;
			Set doGripClose;
			WaitTime 2;
			Reset doGripClose;
		ELSE
			Reset doGripClose;
			Set doGripOpen;
			WaitTime 2;
			Reset doGripOpen;
		ENDIF
	ENDPROC
ENDMODULE
