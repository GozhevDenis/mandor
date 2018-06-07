import turtle

turtle.speed(0)

# Read text data.
data = open('output.dat').read().split('\n')
data = [[float(y) for y in x.split() if y] for x in data if x]

# Extract trajectories.
t = [x[0] for x in data]
z = [x[1] for x in data]
# v = [x[2] for x in data]

# Find bounding boxes.
min_t = min(t)
max_t = max(t)
min_z = min(z)
max_z = max(z)

# Coordinate transformations.
def scr_x(t):
    return -300 + (t - min_t)*(300 - (-300))/(max_t - min_t)

def scr_y(z):
    return -300 + (z - min_z)*(300 - (-300))/(max_z - min_z)

# Move to the start of the plot.
turtle.up()
turtle.goto(scr_x(t[0]), scr_y(z[0]))
turtle.down()

# Draw the plot.
for ti, zi in zip(t, z):
    turtle.goto(scr_x(ti), scr_y(zi))

turtle.Screen().exitonclick()
