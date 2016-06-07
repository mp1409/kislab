using Gadfly
using Cairo

a = readdlm(ARGS[1], ',')
m = match(r"julia/data/(?P<name>\w+)\.csv", ARGS[1])

interval = 5000
time = interval
v = 0
slopes = []

# Testschleife
for line in 2:size(a)[1]
	if a[line, 1] < time
		if a[line, 3] != v
			v = a[line, 3]
			if size(slopes)[1] >= Int(time / interval)
				slopes[Int(time / interval)] += 1
			else 
				append!(slopes, [1])
			end
		end
	else
		time += interval
	end
end

rot = map(x -> (x * 10) / (interval / 1000), slopes)
println(string(m[:name], ": Berechnungen erfolgreich beendet. Plotte Graph..."))

p = plot(
    layer(
        x = map(x -> Int(x * (interval / 1000)), collect(1:size(rot)[1])),
        y = rot[1:end],
        Geom.point,
        Geom.smooth
    ),
    #layer(
    #    x = a[2:end, 1],
    #    y = a[2:end, 3],
    #    Geom.step,
    #    Geom.smooth,
    #    Theme(default_color=colorant"orange")
    #),
    Guide.XLabel("Zeit [s]"),
    Guide.YLabel("U/min"),
    #Guide.manual_color_key(
    #    "Legende",
    #    ["Hall-Sensor", "Optischer Sensor"],
    #    [colorant"cyan", colorant"orange"]
    #),
    # Guide.title(length(ARGS) > 1 ? ARGS[2] : "")
)

draw(PDF(string("images/generated/", m[:name],".pdf"), 8inch, 4inch), p)

