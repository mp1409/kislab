using Gadfly
using Cairo
using CurveFit

a = readdlm(ARGS[1], ',')
m = match(r"julia/data/(?P<name>\w+)\.csv", ARGS[1])

interval = 5000
time = interval
v = 0
slopes = []

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

rot = map(x -> (x * 5) / (interval / 1000), slopes)

# f = curve_fit(LinearFit, map(x -> Float64(x * (interval / 1000)), collect(1:size(rot)[1])), convert(Array{Float64, 1}, rot))
f1 = curve_fit(
        LinearFit, 
        map(x -> Float64(x * (interval / 1000)), collect(1:div(size(rot)[1], 3))), 
        convert(Array{Float64, 1}, rot[1:div(end, 3)])
    )
f2 = curve_fit(
        LinearFit, 
        map(x -> Float64(x * (interval / 1000)), collect(div(size(rot)[1], 3):2 * div(size(rot)[1], 3))), 
        convert(Array{Float64, 1}, rot[div(end, 3):2 * div(end, 3)])
    )
f3 = curve_fit(
        LinearFit, 
        map(x -> Float64(x * (interval / 1000)), collect(2 * div(size(rot)[1], 3):size(rot)[1])), 
        convert(Array{Float64, 1}, rot[2 * div(end, 3):end])
    )


println(string(m[:name], ": Berechnungen erfolgreich beendet."))
println("Approx:")
println(string("\t", f1))
println(string("\t", f2))
println(string("\t", f3))
print("Plotte Graph...")
println()


p = plot(
    layer(
        x = map(x -> Int(x * (interval / 1000)), collect(1:size(rot)[1])),
        y = rot[1:end],
        Geom.point,
        # Geom.smooth
    ),
    # layer(
    #     x =  map(x -> Float64(x * (interval / 1000)), collect(1:size(rot)[1] - 2)),
    #     y = f(map(x -> Float64(x * (interval / 1000)), collect(1:size(rot)[1] - 2))),
    #     Geom.line,
    #     Theme(default_color=colorant"orange")
    # ),
    layer(
        x =  map(x -> Float64(x * (interval / 1000)), collect(1:div(size(rot)[1], 3))),
        y = f1(map(x -> Float64(x * (interval / 1000)), collect(1:div(size(rot)[1], 3)))),
        Geom.line,
        # Theme(default_color=colorant"red")
    ),
    layer(
        x =  map(x -> Float64(x * (interval / 1000)), collect(div(size(rot)[1], 3):2 * div(size(rot)[1], 3))),
        y = f2(map(x -> Float64(x * (interval / 1000)), collect(div(size(rot)[1], 3):2 * div(size(rot)[1], 3)))),
        Geom.line,
        # Theme(default_color=colorant"red")
    ),
    layer(
        x =  map(x -> Float64(x * (interval / 1000)), collect(div(2 * size(rot)[1], 3):size(rot)[1])),
        y = f3(map(x -> Float64(x * (interval / 1000)), collect(div(2 * size(rot)[1], 3):size(rot)[1]))),
        Geom.line,
        # Theme(default_color=colorant"red")
    ),
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

