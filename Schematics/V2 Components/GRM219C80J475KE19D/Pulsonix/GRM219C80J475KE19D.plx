PULSONIX_LIBRARY_ASCII "SamacSys ECAD Model"
//343387/1385372/2.50/2/5/Capacitor

(asciiHeader
	(fileUnits MM)
)
(library Library_1
	(padStyleDef "r139_91"
		(holeDiam 0)
		(padShape (layerNumRef 1) (padShapeType Rect)  (shapeWidth 0.91) (shapeHeight 1.39))
		(padShape (layerNumRef 16) (padShapeType Ellipse)  (shapeWidth 0) (shapeHeight 0))
	)
	(textStyleDef "Normal"
		(font
			(fontType Stroke)
			(fontFace "Helvetica")
			(fontHeight 1.27)
			(strokeWidth 0.127)
		)
	)
	(patternDef "CAPC2012X95N" (originalName "CAPC2012X95N")
		(multiLayer
			(pad (padNum 1) (padStyleRef r139_91) (pt -0.82, 0) (rotation 0))
			(pad (padNum 2) (padStyleRef r139_91) (pt 0.82, 0) (rotation 0))
		)
		(layerContents (layerNumRef 18)
			(attr "RefDes" "RefDes" (pt 0, 0) (textStyleRef "Normal") (isVisible True))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.425 0.85) (pt 1.425 0.85) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.425 0.85) (pt 1.425 -0.85) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt 1.425 -0.85) (pt -1.425 -0.85) (width 0.05))
		)
		(layerContents (layerNumRef Courtyard_Top)
			(line (pt -1.425 -0.85) (pt -1.425 0.85) (width 0.05))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1 0.625) (pt 1 0.625) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 1 0.625) (pt 1 -0.625) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt 1 -0.625) (pt -1 -0.625) (width 0.025))
		)
		(layerContents (layerNumRef 28)
			(line (pt -1 -0.625) (pt -1 0.625) (width 0.025))
		)
		(layerContents (layerNumRef 18)
			(line (pt 0 0.525) (pt 0 -0.525) (width 0.2))
		)
	)
	(symbolDef "GRM219C80J475KE19D" (originalName "GRM219C80J475KE19D")

		(pin (pinNum 1) (pt 0 mils 0 mils) (rotation 0) (pinLength 200 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 0 mils -35 mils) (rotation 0]) (justify "UpperLeft") (textStyleRef "Normal"))
		))
		(pin (pinNum 2) (pt 500 mils 0 mils) (rotation 180) (pinLength 200 mils) (pinDisplay (dispPinName false)) (pinName (text (pt 500 mils -35 mils) (rotation 0]) (justify "UpperRight") (textStyleRef "Normal"))
		))
		(line (pt 220 mils 100 mils) (pt 220 mils -100 mils) (width 6 mils))
		(line (pt 280 mils 100 mils) (pt 280 mils -100 mils) (width 6 mils))
		(line (pt 200 mils 0 mils) (pt 220 mils 0 mils) (width 6 mils))
		(line (pt 280 mils 0 mils) (pt 300 mils 0 mils) (width 6 mils))
		(attr "RefDes" "RefDes" (pt 350 mils 250 mils) (justify 24) (isVisible True) (textStyleRef "Normal"))
		(attr "Type" "Type" (pt 350 mils 150 mils) (justify 24) (isVisible True) (textStyleRef "Normal"))

	)
	(compDef "GRM219C80J475KE19D" (originalName "GRM219C80J475KE19D") (compHeader (numPins 2) (numParts 1) (refDesPrefix C)
		)
		(compPin "1" (pinName "1") (partNum 1) (symPinNum 1) (gateEq 0) (pinEq 0) (pinType Unknown))
		(compPin "2" (pinName "2") (partNum 1) (symPinNum 2) (gateEq 0) (pinEq 0) (pinType Unknown))
		(attachedSymbol (partNum 1) (altType Normal) (symbolName "GRM219C80J475KE19D"))
		(attachedPattern (patternNum 1) (patternName "CAPC2012X95N")
			(numPads 2)
			(padPinMap
				(padNum 1) (compPinRef "1")
				(padNum 2) (compPinRef "2")
			)
		)
		(attr "Mouser Part Number" "81-GRM219C80J475KE9D")
		(attr "Mouser Price/Stock" "https://www.mouser.co.uk/ProductDetail/Murata-Electronics/GRM219C80J475KE19D?qs=1H9tZOlVdUAU5TSvoHHPuA%3D%3D")
		(attr "Manufacturer_Name" "Murata Electronics")
		(attr "Manufacturer_Part_Number" "GRM219C80J475KE19D")
		(attr "Description" "Murata 0805 GRM 4.7uF Ceramic Multilayer Capacitor, 6.3 V dc, +105C, X6S Dielectric, +/-10% SMD")
		(attr "<Hyperlink>" "http://www.murata.com/~/media/webrenewal/support/library/catalog/products/capacitor/mlcc/c02e.pdf")
		(attr "<Component Height>" "0.95")
		(attr "<STEP Filename>" "GRM219C80J475KE19D.stp")
		(attr "<STEP Offsets>" "X=0;Y=0;Z=0")
		(attr "<STEP Rotation>" "X=0;Y=0;Z=0")
	)

)