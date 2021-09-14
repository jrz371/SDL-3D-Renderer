import sys

try:
	filename = sys.argv[1]
	new_filename = sys.argv[2]

	buffer = []
	faces = []

	with open(filename, "r") as f:
		buffer = f.readlines();
		buffer = [line.rstrip() for line in buffer]
		f.close()

	for line in buffer:
		if 'f' in line and '#' not in line:
			line = line.replace("f ", "")
			faces.append(line)

	with open(new_filename, "w") as f:
		for line in buffer:
			if 'f' not in line and '#' not in line:
				f.write(line + "\n")

		for line in faces:
			try:
				face = line.split(" ")
				
				s = "f " + face[0].split("/")[0] + " " + face[1].split("/")[0] + " " + face[2].split("/")[0] + "\n";

				print(s)
				f.write(s)
			except:
				pass

		f.close()

except:
	print("Usage: python parser.py <OBJ file> <new OBJ file>")