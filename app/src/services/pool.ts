// src/services/relayPool.ts
import { RelayPool } from '@/services/relaysPool';
import { relays } from '@/constants/Relays';

declare global {
    interface Window {
        relayPool: RelayPool | undefined;
    }
}

// Inicialize a variável global se ela ainda não existir
if (typeof window !== 'undefined' && !window.relayPool) {
    window.relayPool = new RelayPool(relays)
    window.relayPool.connect()
}

export const getRelayPool = () => {
    return window.relayPool;
};

