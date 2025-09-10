import { Relay } from "@/types/types"
import { RelayItem } from "./RelayItem"

interface RelayProps {
    relays: Relay[]
}

export const RelaySearchResults = async ({ relays }: RelayProps) => {
    
    return (
        <div className="w-full">
            <div className='w-full grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-2 md:gap-7 py-5 md:py-8 px-3 md:px-6'>
                { 
                    relays.map((relay, index) => <RelayItem key={index} relay={relay} />)
                }
            </div>
            <div className="w-full h-10"></div>
        </div>
    )
}

