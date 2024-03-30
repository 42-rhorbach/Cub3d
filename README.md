# CUB3D


# CHECKS TO BE DONE BEFORE HANDING IN

check all headers, are al 'includes' needed, or could we clean them up a bit
maybe put the includes in the header files instead of the .c files?

clean up code, check for dubble not used vars, or unnecessary code blocks
check varaibles that are used multiple times, and store them in the correct struct, or maybe add a struct with some basic used vars.

check for checks, do we have potenial segfaults or mem leaks.

check edge cases, is the parsing correct, does it fail in some specific cases

check error messages, we could define them in the header, or make a different function, the current fuction is to long.
could also combine error messages, so we have less specifc ones.

add textures, make sure they work.

decide if we want to update minimap or remove it from the final version, we can keep it for our own github version.
if we keep it, fix the scale and/or implement a remove key-code.
we could try to print 10 blocks to the right, left, up and down. then the map will have a fixed size which will always work and wil always fit.

check the rays in the minimap and normal game, there are still some empty rays in the rays on the minimap.





#     WHAT NEEDS TO BE DONE

finding textures

projecting textures on walls correctly

walking forward using "W" in the look direction not true North

smoother edges along the walls






#     KNOWN ISSUES
hitting wall creates floating point exception(see below) (or walking too long? not this for so far I can see), actually, turning while next to a wall crashes with floating point
(specifically having turned before hitting a wall breaks it)
(it is possible while it tries to reverse the move something saves regardless of if the move was legal or not and then the missalignment creates a floating point) [FIXED?, no longer crashes, but unclear why]

walking sideways and parallel to the jagged wall sometimes invert controls until angle is adjusted with arrow keys

edges are not correct, too staircase like
(depth? conversion?) [FIXED on north and west side]

edges jagged on south and east side, walls are not fully shown (half planes and gaps)

# Debugging with gdb

`DEBUG=1 make`
`gdb --args ./cub3D test_files/test3.cub`
`r` to run the program until any breakpoint
`b ft_ray_loop` to set a breakpoint in the `ft_ray_loop` function
`p data.px` to print the player's X coordinate
