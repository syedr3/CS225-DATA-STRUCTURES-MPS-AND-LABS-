# Assignment Information (these are the *only* things you need to change here between assignments)
set(assignment_name "mp_mosaics") # Name of the assignment
set(assignment_version 1.2023.05.0) # Version, where minor=semester_year, patch=semester_end_month, tweak=revision
set(assignment_entrypoints "mosaics") # Entrypoints to run the program
set(assignment_clean_rm
        "gridtest-actual.png"
        "kdtree_1_10-actual.kd"
        "kdtree_2_2-actual.kd"
        "kdtree_2_10-actual.kd"
        "kdtree_2_20-actual.kd"
        "kdtree_3_10-actual.kd"
        "kdtree_3_14-actual.kd"
        "kdtree_3_31-actual.kd") # Generated files that should be removed with "make clean"
set(assignment_container "sp23") # Container we are targetting