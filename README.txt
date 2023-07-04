 _______   ___   _ _____ _   _  _____ _____ _____ _____   _____  _   _   ___   _      _      _____ _   _ _____  _____ 
/  ___\ \ / / \ | |_   _| | | ||  ___/  ___|_   _/  ___| /  __ \| | | | / _ \ | |    | |    |  ___| \ | |  __ \|  ___|
\ `--. \ V /|  \| | | | | |_| || |__ \ `--.  | | \ `--.  | /  \/| |_| |/ /_\ \| |    | |    | |__ |  \| | |  \/| |__  
 `--. \ \ / | . ` | | | |  _  ||  __| `--. \ | |  `--. \ | |    |  _  ||  _  || |    | |    |  __|| . ` | | __ |  __| 
/\__/ / | | | |\  | | | | | | || |___/\__/ /_| |_/\__/ / | \__/\| | | || | | || |____| |____| |___| |\  | |_\ \| |___ 
\____/  \_/ \_| \_/ \_/ \_| |_/\____/\____/ \___/\____/   \____/\_| |_/\_| |_/\_____/\_____/\____/\_| \_/\____/\____/ 

This is a collection of programs designed to solve a design challenge I encountered in my studies.
The synthesis challenge was a set of two assignments where we were tasked to design and optimize a gear system, given some constraints and a scoring system.
In both challenges, we could choose a set number of positions to place our gear shafts and the sizes of the gears they would hold.
Both scripts were not designed with speed in mind, although they were lightly optimized. This was because, theoretically, they would run only once, and then I would have my answer.

Synthesis Challenge 1 was a simple 8:1 gear train. I made a script that cycles through every possible arrangement of shafts, and for each arrangement cycles through a wide range of radii for the initial gear.
These two variables were enough to completely constrain the design of the gear train so that the score could be calculated and saved.

Synthesis Challenge 2 was a more complex 12:1 reduction ratio, utilizing a compound gear train. It additionally allowed for leniency in the dimensions.
To solve it, I made many different scripts that tested a slightly different initial gears setup. I eventually tested a setup where all shafts had one gear except for the first, which had two. It was very difficult to find the optimal configuration, but I eventually found a way.
Essentially twisting a collection of dials to see what was best, I nested three for loops to test different spacing configurations between shafts. Within that nest, I nested another three for loops to vary the radii of the first gear on both sides, and the final gear. This is probably not good practice, but it was the most intuitive concept I had.
Finally, tweaks were done by hand before submission.

Scoring for the challenges were relative to the rest of the cohort. I am pleased to say that I earned 4.00/4.00 marks for these challenges.

Synthesis Challenge 1 was developed from March 15 to March 17 2023
Synthesis Challenge 2 was developed from March 21 to March 24 2023
