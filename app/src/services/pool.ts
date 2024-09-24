// src/services/relayPool.ts
import { RelayPool } from '@/services/relaysPool';
import { relays } from '@/constants/Relays';

const relayPool = new RelayPool(relays)

export const initializeRelayPool = async () => {
    if(relayPool.websockets.length <= 0)
        await relayPool.connect()

    console.log("relayPool initialized")
}

export const getRelayPool = (): RelayPool => {

    if(relayPool.websockets.length <= 0)
        throw new Error("relayPool not initialized or connected")

    return relayPool
}

