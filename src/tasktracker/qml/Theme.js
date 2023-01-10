.pragma library

function colorWithAlpha(color, alpha) {
    return Qt.hsla(color.hslHue, color.hslSaturation, color.hslLightness, alpha)
}

const ErrorTextColor = "#ff0000"
const ErrorTextHeight = 11

const PageHeaderHeight = 40

const ConfigLeftContentMargin = 10
const ConfigRightContentMargin = 10
const ConfigItemHeight = 28
const ConfigGroupTitleHeight = 40
const ConfigGroupTitleBottomMargin = 4
const ConfigGroupTitleFontWeight = 400

const DialogRadius = 12
const DialogPadding = 20
const DialogButtonsHeight = 40
