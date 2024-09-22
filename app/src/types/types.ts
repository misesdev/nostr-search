
export type SearchParams = {
    searchTerm?: string,
    pubkey?: string
}

export type User = {
    name: string,
    displayName: string,
    profile: string,
    pubkey: string,
    about?: string,
    similarity: number
}
