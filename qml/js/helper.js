function getPluralNames(count, idx, plural, lang) {
    var ret;
//    if (count === 2) {
//        ret = (idx === 0) ? qsTr("Singular") : qsTr("Plural")
//    } else {
//        switch(lang) {
//        case "ar":
//        case "ar_EG":
//        case "ar_SA":
//        case "ar_SD":
//        case "ar_SY":
//        case "ar_AA":
//            switch(plural) {
//            case "0":
//                ret = qsTr("Zero")
//                break;
//            case "1":
//                ret = qsTr("One")
//                break;
//            case "2":
//                ret = qsTr("Two")
//                break;
//            case "3":
//                ret = qsTr("Few")
//                break;
//            case "4":
//                ret = qsTr("Many")
//                break;
//            case "5":
//                ret = qsTr("Other")
//                break;
//            }
//            break;
//        case "be":
//        case "be_BY":
//        case "be@tarask":
//            switch(plural) {
//            case "1":
//                ret = qsTr("One")
//                break;
//                case
//            }
//        }
//    }

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
