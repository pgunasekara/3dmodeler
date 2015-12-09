#readme.txt
Group:
	Name: Pasindu Gunasekara
		MacID: gunasepi
		StudentNumber: 001412155

	Name: Roberto Temelkovski
		MacID: temelkr
		Student Number: 001418731

Bonus Features Implemented:
	9. Camera Control
		-The user can both fly around the scene and control the camera rotation with the mouse

Known Issues:
	Sometimes deleting an object may not automatically select a deselected node.

	When Changing materials, you cannot change the material of the first node without first changing the material of the second node added. I'm not entirely sure why this happens. Changing materials works perfectly fine after you change any other node before the first one.

Sources:
	Material Values: http://devernay.free.fr/cours/opengl/materials.html
	File I/O: http://www.cplusplus.com/doc/tutorial/files/
	Keyboard Modifiers: http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard/

Extra Notes:
	Sometimes on Linux or OSX the main file object generation may not work. For Linux, it's because the c++11 flag is not included for some reason. If so, run this command first,
		g++ -std=c++11 -c -o main.o main.cpp
	then run
		make

	If on OSX, and you get an error about incorrect architecture, then try,
		g++ -std=c++11 -arch x86_64  -c -o main.o main.cpp
	then run
		make

	Everything should compile properly now.