
export type SearchParams = {
    searchTerm?: string,
    pubkey?: string
}

export type RelayParams = {
    searchTerm: string
}

export type User = {
    name: string,
    displayName: string,
    profile: string,
    pubkey: string,
    about?: string,
    similarity: number
}

export type Relay = {
    relay: string,
    similarity: number
}

export type RelayInfo = {
    name?: string,
    icon?: string,
    limitation?: any,
    description?: string,
    software?: string,
    supported_nips?: number[],
    version?: string,
    address?: string,
    contact?: string
}
