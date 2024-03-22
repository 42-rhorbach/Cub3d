# CUB3D



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
