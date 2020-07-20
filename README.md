# Visualizing US GDP Data in C++
Using QT library, data from https://fred.stlouisfed.org/series/GDP will be visually plotted.

## Compiling
```
qmake
make
```

## Use
Before running a file named 'US_GDP.csv' must be placed in the same directory as the program. It should have to columns, the first is the date in the format "yyyy-MM-dd" and the second is the GDP in billions as a floating point value.

Hover over the line to see the value for that date, click on the line to make that information permenant.
