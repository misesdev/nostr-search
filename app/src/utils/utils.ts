import { bech32 } from "bech32"

export type Hex = Uint8Array | string | number[]

export function bytesToHex(bytes: Hex): string {

    if (bytes.length <= 0)
    throw new Error("The byte array is empty!")
    if(typeof(bytes) == "string")
    throw new Error("Expected the type Uint8Array")

    let hexValue: string = ""

    bytes.forEach(byte => {
        let hexNumber = byte.toString(16)
        if (hexNumber.length == 1)
        hexNumber = "0" + hexNumber

        hexValue += hexNumber
    })

    return hexValue
}

export function hexToBytes(hex: string, hexadecimal: boolean = true): Uint8Array {
    if (!!!hex)
    throw new Error("hex is undefined or empty!")
    if (hexadecimal && hex.length % 2 !== 0)
    throw new Error("Invalid hex value!")

    let bytes = new Uint8Array(hexadecimal ? hex.length / 2 : hex.length)

    for (let i = 0; i <= hex.length; i += hexadecimal ? 2 : 1)
        if (hexadecimal)
            bytes[i / 2] = parseInt(hex.substring(i, i + 2), 16)
        else
            bytes[i] = hex.charCodeAt(i)

    return bytes;
}

export const validatePubkey = (pubkey: string) => {
    try 
    {
        let npub = bech32.decode(pubkey)

        let data = bech32.fromWords(npub.words)

        let hexpub = Buffer.from(data).toString('hex')

        return hexpub

    } catch { return '' }
}

export const hexToNpub = (hex: string) => {

    const bytes = hexToBytes(hex)

    const words = bech32.toWords(bytes)

    return bech32.encode('npub', words)
}



