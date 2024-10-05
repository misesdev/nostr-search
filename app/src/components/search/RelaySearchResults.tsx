import { Relay } from "@/types/types"
import { RelayItem } from "./RelayItem"

type RelayProps = {
    relays: Relay[]
}

export const RelaySearchResults = async ({ relays }: RelayProps) => {
    
    return (
        <div className='w-full grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 xl:grid-cols-4 gap-4 md:gap-7 py-5 md:py-8 px-3 md:px-6'>
            { 
                relays.map(async (relay, index) => <RelayItem key={index} relay={relay.relay} />)
            }
        </div>
    )
}
