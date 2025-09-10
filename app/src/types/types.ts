
export type SearchParams = {
    searchTerm?: string,
    pubkey?: string
}

export type RelayParams = {
    searchTerm: string
}

export type User = {
    name: string;
    pubkey: string;
    display_name: string;
    picture: string;
    about: string;
    banner: string;
    website?: string;
    nip05?: string;
    lud06?: string;
    lud16?: string;
    zapService?: string;
    ref_count: number;
}

export type Relay = {
    url: string;
    name: string;
    pubkey?: string;
    description?: string;
    contact?: string;
    supported_nips: string;
    software?: string;
    version?: string;
    active: boolean;
    ref_count: number;
    icon?: string;
    author?: User;
}

