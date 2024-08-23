import { getRelays } from "./src/relays";
import NDK from "@nostr-dev-kit/ndk"

const getConnection = async () : Promise<NDK> => {

    const relays = getRelays()

    const ndk = new NDK({ explicitRelayUrls: relays })

    await ndk.connect()

    return ndk
}

const main = async () => {
   
    const Nostr = await getConnection();
        
    console.log("connected")

    const hexPubkey = "55472e9c01f37a35f6032b9b78dade386e6e4c57d80fd1d0646abb39280e5e27"

    const events = await Nostr.fetchEvent({  authors: [hexPubkey], kinds: [0, 1], limit: 10 }) 

    console.log("events results:", events)
}



main() 



