# Assignment Information (these are the *only* things you need to change here between assignments)
set(assignment_name "mp_mazes") # Name of the assignment
set(assignment_version 1.2023.05.0) # Version, where minor=semester_year, patch=semester_end_month, tweak=revision
set(assignment_entrypoints "main" "testdsets" "testsquaremaze") # Entrypoints to run the program
set(assignment_clean_rm "unsolved-actual.png"
                        "solved-actual.png"
                        "testDrawMazeSmall-actual.png"
                        "testDrawMazeLarge-actual.png"
                        "testDrawSolutionMed-actual.png"
                        "testDrawSolutionLarge-actual.png") # Generated files that should be removed with "make clean"
set(assignment_container "sp23") # Container we are targetting