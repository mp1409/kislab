# Julia-Script um die CSV-Dateien zu plotten.
# Erste Zeile des CSV Datei wird als Achsenbeschriftung genutzt.
# CSV Dateiname als Name für resultierende PDF.
# Title verwendet zweites Kommandozeilenargument, wird allerdings aufgrund automatischer Erzeugung nicht genutzt.

using Gadfly
using Cairo

a = readdlm(ARGS[1], ';');
m = match(r"julia/(?P<name>\w+)\.csv", ARGS[1])

p = plot(
    layer(
        x = a[2:end, 1],
        y = a[2:end, 2],
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
    Guide.XLabel(a[1,1]),
    Guide.YLabel(a[1,2]),
    #Guide.manual_color_key(
    #    "Legende",
    #    ["Hall-Sensor", "Optischer Sensor"],
    #    [colorant"cyan", colorant"orange"]
    #),
    Guide.title(length(ARGS) > 1 ? ARGS[2] : "")
)

draw(PDF(string("images/generated/", m[:name], ".pdf"), 8inch, 4inch), p)
