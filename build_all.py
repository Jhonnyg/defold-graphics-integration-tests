import os, shutil, subprocess

cwd = os.getcwd()

all_files = os.listdir(cwd)

dynamo_home = os.getenv('DYNAMO_HOME')

if dynamo_home == None:
	print("No $DYNAMO_HOME specified.")
	exit(-1)

bob_path = os.path.join(dynamo_home, 'share', 'java', 'bob.jar')

for x in all_files:

	os.chdir(cwd)

	if os.path.isdir(x) and not x.startswith('.'):
		os.chdir(x)
		shutil.rmtree('build', ignore_errors=True)
		subprocess.run(["java", "-jar", bob_path, "--debug-output-spirv=true", "resolve", "build"])
