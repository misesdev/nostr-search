import { getRelays } from "./src/relays";
import NDK from "@nostr-dev-kit/ndk"

const getConnection = async () : Promise<NDK> => {

    const relays = getRelays()

    const ndk = new NDK({ explicitRelayUrls: relays })

    await ndk.connect()

    return ndk
}

const main = async () : Promise<void> => {
   
    const Nostr = await getConnection()

    const npub = "1739d937dc8c0c7370aa27585938c119e25c41f6c441a5d34c6d38503e3136ef"

    const events = await Nostr.fetchEvent({  authors: [npub], kinds: [3], limit: 1 })

    console.log("events results:", events)

    console.log("search relays", Nostr.explicitRelayUrls)
}

//(async () => { await init() })();

main()

