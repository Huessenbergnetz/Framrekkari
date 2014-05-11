function getPluralNames(count, idx, plural, lang) {
    var ret;
    switch(plural) {
    case "0":
        ret = qsTr("Zero");
        break;
    case "1":
        ret = qsTr("Singular");
        break;
    case "2":
        ret = qsTr("Two")
        break;
    case "3":
        ret = qsTr("Few")
        break;
    case "4":
        ret = qsTr("Many")
        break;
    case "5":
        ret = qsTr("Plural")
        break;
    }

    return ret;
}


function getAccountIcon(type, size)
{
    switch(type)
    {
    case 0:
    default:
        return "/usr/share/harbour-framrekkari/icons/icon-"+ size +"-transifex.png"
    }
}
