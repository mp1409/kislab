# Julia-Script um schematisches Diagramm zu erzeugen

using Gadfly
using Cairo

x1 = []
y1 = []

x2 = []
y2 = []

for i = 0:11
    append!(x1, [i * 32.8])
    append!(y1, [i % 2])
end

y1 *= 0.99
y1 += 0.005


for i in [0,1,2,3]
    append!(x2, [i * 120])
    append!(y2, [i % 2])
end

p = plot(
    layer(
        x = x1,
        y = y1,
        Geom.step,
        Theme(default_color=colorant"orange")
    ),
    layer(
        x = x2,
        y = y2,
        Geom.step,
    ),
    Guide.XLabel("Drehwinkel in Grad"),
    Guide.YLabel("Sensor"),
    Guide.manual_color_key(
        "Legende",
        ["Hall-Sensor", "Optischer Sensor"],
        [colorant"cyan", colorant"orange"]
    ),
    # Guide.title("Sensorenwerte")
)
draw(PDF("images/generated/sensor_messwerte1.pdf", 8inch, 4inch), p)
