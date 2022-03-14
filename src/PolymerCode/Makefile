all:
	gcc -O3 driveMetropolis.c -o metropolis.out -lm


run:
	gcc -O3 driveMetropolis.c -o metropolis.out -lm

	./metropolis.out parameters.txt outputTest.txt 0 2 30 3 -1 -1 -1

batch:

	gcc -O3 driveMetropolis.c -o metropolis.out -lm

	chmod a+x runBatch.sh

	./runBatch.sh

hpc:

	gcc -O3 driveMetropolis.c -o metropolis.out -lm
	
	chmod a+x makePubs.pl

	./makePubs.pl

	chmod a+x submit.pl

	./submit.pl

copyrepo:

	git -C ~/Documents/PolymerGit log -1 --pretty=format:%H > "CommitUsedHash.txt"

	rsync -r ~/Documents/PolymerGit/src/PolymerCode/ . --exclude='.git'

parallel:

	gcc -O3 driveMetropolis.c -o metropolis.out -lm

	chmod a+x batchMetropolis.sh

	./batchMetropolis.sh 7 v

copycat:
	chmod a+x copyCatFiles.sh

	./copyCatFiles.sh
